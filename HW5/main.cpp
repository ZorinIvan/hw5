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
			Directory new_dir(tokens[1], cwd); /*Create a new directory with this name and the current parent folder*/
        }

        if (tokens[0] == "cat")
        {
			File* needed_file = cwd->GetFileByName(tokens[1]); /*Get the text file*/
			if (needed_file == NULL ) /*File not found*/
				continue;
			/*Need to add check if this is a text file*/
			cout << dynamic_cast<TextFile*>(needed_file)->getText() /*If not print this file*/ << endl;
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
                // Insert code here...
            }

            // Output redirect ">>"
            if (params.size() == 2 && params[0] == ">>")
            {
                // Insert code here...
            }
            
            cerr << "Parse error while parsing " << tokens[0] << endl;
        }

        if (tokens[0] == "pwd")
        {
			cout << cwd->getPath() << endl; /*Printing the current path*/
        }

        if (tokens[0] == "ls")
        {
            // Insert code here...
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
            // Insert code here...
        }

        if (tokens[0] == "exit")
        {
            break;
        }
    }

    delete root;
    return 0;
}
