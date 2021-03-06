#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "File.h"
#include "TextFile.h"
#include "Directory.h"
#include "FilesIterator.h"

using namespace std;

//*********************************************************************************************
//* Name:           tokenize
//* Description:    Split a string to tokens based on given delimiters
//* Parameters:     string line - the input string
//*                 char* delim - a string of delimiters
//* Return value:   vector<string> - vector containing the split string
//*********************************************************************************************
vector<string> tokenize(string line, const char* delim)
{
    unsigned int i, j;
    vector<string> tokens;
    while (!line.empty())
    {
        i = line.find_first_not_of(delim);
        j = line.find_first_of(delim, i + 1);
        tokens.push_back(line.substr(i, j - i));
        if (j > line.size() - 1)
            line = "";
        else
            line = line.substr(j + 1, line.size() - j - 1);
    }
    return tokens;
}

// A helper class for implementing the "find" command
// This class accepts a string in the constructor to be matched against the file name.
// The class also implement the () operator which accepts a file, this method compare the
// file's name against the string from the constructor and return true if there's a partial match
class FindHelper
{
public:
    FindHelper(string st) :
            m_string(st)
    {
    }

    //*********************************************************************************************
    //* Name:           operator()
    //* Description:    Implements the function call operator
    //* Parameters:     File file - the file to compare against
    //* Return value:   bool - true if both files name matches the string m_string
    //*
    //* Note:           Since the class implements the function call operator that accepts a single
    //*                 parameter and returns bool, an object of this class can be used as a
    //*                 parameter to the find_if function and many other functions in the 
    //*                 <algorithm> library
    //*********************************************************************************************
    bool operator()(File& file)
    {
        if (file.getName().find(m_string) != string::npos)
        {
            return true;
        }

        return false;
    }

private:
    string m_string;
};


// A helper class for implementing the "grep" command
// This class accepts a string in the constructor to be matched against text in the file.
// The class also implement the () operator which accepts a Textfile, this method compares the
// file's text against the string from the constructor and returns true if there's a partial match
class FindTextHelper
{
public:
    FindTextHelper(string st) :
            m_string(st)
    {
    }

    //*********************************************************************************************
    //* Name:           operator()
    //* Description:    Implements the function call operator
    //* Parameters:     File file - the file to compare against
    //* Return value:   bool - true if file's text matches the string m_string
    //*********************************************************************************************

    bool operator()(File& file)
    {
    	TextFile* textfile = dynamic_cast<TextFile*>(&file);
        if (NULL!=textfile && textfile->getText().find(m_string) != string::npos)
        {
            return true;
        }

        return false;
    }

private:
    string m_string;
};




int main()
{
    Directory* root = new Directory("root");
    Directory* cwd = root;

    const char* delims = " \t\n";
    vector<string> tokens;
    string line;

    while (!cin.eof())
    {
        getline(cin, line);
        tokens = tokenize(line, delims);

        if (tokens.size() == 0)
        {
            continue;
        }

        if (tokens[0] == "cd")
        {
            if (tokens.size() == 2)
            {
                File *pFile = NULL;
                if (".." == tokens[1])
                {
                    // cd ..
                    pFile = cwd->getParrent();
                }
                else
                {
                    // cd <dir>
                    pFile = cwd->GetFile(tokens[1]);
                }

                // Check if pFile is NULL or if it's not pointing to a directory
                Directory* pDir = dynamic_cast<Directory*>(pFile);

                /*!!!!! if not necessary !!!!!*/
                if (NULL != pDir)
                {
                    cwd = pDir;
                    continue;
                }
            }

            cerr << "Parse error while parsing " << tokens[0] << endl;
        }

        if (tokens[0] == "mkdir")
        {
        	if(tokens.size()!=2){
        		cerr << "Parse error while parsing " << tokens[0] << endl;
        		continue;
        	}

			Directory* new_dir = new Directory(tokens[1], cwd); /*Create a new directory with this name and the current parent folder*/
			if (cwd->AddFile(new_dir) == false)
			{
				delete new_dir;
				cerr << "Parse error while parsing " << tokens[0] << endl;
			}
        }

        if (tokens[0] == "cat")
        {
        	if(tokens.size()!=2){
        		cerr << "Parse error while parsing " << tokens[0] << endl;
        		continue;
        	}
			File* needed_file = cwd->GetFile(tokens[1]); /*Get the text file*/
			if (needed_file == NULL) /*File not found*/
			{
				cerr << "Parse error while parsing " << tokens[0] << endl;
				continue;
			}
			TextFile* needed_file_text = dynamic_cast<TextFile*>(needed_file);
			if (NULL == needed_file_text) /*If this is not a TextFile file*/
			{
				cerr << "Parse error while parsing " << tokens[0] << endl;
				continue;
			}
			/*Need to add check if this is a text file*/
			cout << needed_file_text->getText() /*If not print this file*/ << endl;
        }

        if (tokens[0] == "echo")
        {
            // Try to match the message between the ""
            vector<string> message = tokenize(line, "\"");

            // If we only have the message
            if (message.size() == 2)
            {
                cout << message[1] << endl;
                continue;
            }

            // Message[1] should hold the message and message[2] should hole the other parameters
            vector<string> params = tokenize(message[2], delims);

            // Output redirect ">"
            if (params.size() == 2 && params[0] == ">")
            {
				File* old_file = cwd->GetFile(params[1]);
				if (old_file == NULL) /*It didn't exist yet*/
				{
					TextFile* new_textfile = new TextFile(params[1], cwd, message[1]);
					cwd->AddFile(new_textfile);
				}
				else
				{
					if (dynamic_cast<TextFile*>(old_file) == NULL) /*This is not a text file*/
					{
						cerr << "Parse error while parsing " << tokens[0] << endl;
						continue;
					}
					dynamic_cast<TextFile*>(old_file)->updateText(message[1]);
				}
            }

            // Output redirect ">>"
			else if (params.size() == 2 && params[0] == ">>")
			{
				File* old_file = cwd->GetFile(params[1]);
				if (old_file == NULL) /*Doesn't exist yet*/
				{
					TextFile* new_textfile = new TextFile(params[1], cwd, message[1]);
					cwd->AddFile(new_textfile);
				}
				else
				{
					TextFile* new_textfile = dynamic_cast<TextFile*>(old_file);
					if (new_textfile == NULL) /*Not a text file*/
					{
						cerr << "Parse error while parsing " << tokens[0] << endl;
						continue;
					}
					else
					{
						new_textfile->addText(message[1]);
						continue;
					}
				}
			}  
			else{ /*If both conditions dont work*/
				cerr << "Parse error while parsing " << tokens[0] << endl;
				continue;
			}
        }

        if (tokens[0] == "pwd")
        {
        	if(tokens.size()!=1){
        		cerr << "Parse error while parsing " << tokens[0] << endl;
        		continue;
        	}
			cout << cwd->getPath() << endl; /*Printing the current path*/
        }

        if (tokens[0] == "ls")
        {
        	if(tokens.size()!=1){
        		cerr << "Parse error while parsing " << tokens[0] << endl;
        		continue;
        	}
			int length = cwd->GetNumOfFiles();
			for (int i = 0; i < length;i++)
			{
				cout << cwd->getFileByPlace(i)->getName() << endl;
			}
        }

        if (tokens[0] == "find")
        {
            // Check number of parameters
            if (tokens.size() == 2)
            {
                FilesIterator itB = cwd->begin();
                FilesIterator itE = cwd->end();

                // Initialize findHeleper with our search string
                FindHelper findHelper(tokens[1]);

                // Use find_if to search for file that return true for our helper function
                FilesIterator it = find_if(itB, itE, findHelper);
                while (it != itE)
                {
                    cout << "found: " << it->getfullName() << endl;
                    it++;

                    // Since find_if returns the first match, keep calling it until we reach the 
                    // end of our tree
                    it = find_if(it, itE, findHelper);
                }

                continue;
            }

            cerr << "Parse error while parsing " << tokens[0] << endl;
        }

        if (tokens[0] == "grep")
        {
            // Check number of parameters
            if (tokens.size() == 2)
            {
                FilesIterator itB = cwd->begin();
                FilesIterator itE = cwd->end();

                // Initialize findHeleper with our search string
                FindTextHelper findHelper(tokens[1]);

                // Use find_if to search for file that return true for our helper function
                FilesIterator it = find_if(itB, itE, findHelper);
                while (it != itE)
                {
                    cout << "found: " << it->getfullName() << endl;
                    it++;

                    // Since find_if returns the first match, keep calling it until we reach the
                    // end of our tree
                    it = find_if(it, itE, findHelper);
                }

                continue;
            }

            cerr << "Parse error while parsing " << tokens[0] << endl;
        }

		if (tokens[0] == "rm")
		{
			if (tokens.size() != 2) /*Not enough parameters*/
			{
				cerr << "Parse error while parsing " << tokens[0] << endl;
				continue;
			}
			else
			{
				File* deleted_file = cwd->GetFile(tokens[1]);
				if (deleted_file == NULL) /*File not found*/
				{
					cerr << "Parse error while parsing " << tokens[0] << endl;
					continue;
				}
				if (cwd->RemoveFile(tokens[1]) == false) //will call the d'tor of file. It's a virtual method so a right d'tor will be called.
				{
					cerr << "Parse error while parsing " << tokens[0] << endl;
					continue;
				}
			}
		}

        if (tokens[0] == "exit")
        {
        	if(tokens.size()!=1){
        		cerr << "Parse error while parsing " << tokens[0] << endl;
        		continue;
        	}
            break;
        }

    	if(tokens[0]=="print")
    	{
        	if(tokens.size()!=1){
        		cerr << "Parse error while parsing " << tokens[0] << endl;
        		continue;
        	}

            FilesIterator itB = cwd->begin();
            FilesIterator itE = cwd->end();

            while(itB!=itE)
            {
            	itB->print();
            	itB++;
            }
    	}

		if (tokens[0] != "mkdir" && tokens[0] != "pwd" && tokens[0] != "cd" && tokens[0] != "rm" && tokens[0] != "cat" && tokens[0] != "echo" && tokens[0] != "ls" && tokens[0] != "print" && tokens[0] != "find" && tokens[0] != "grep" && tokens[0] != "exit")
		{
			cerr << "Parse error while parsing " << tokens[0] << endl;
			continue;
		}

    }//while



    delete root;
    return 0;
}
