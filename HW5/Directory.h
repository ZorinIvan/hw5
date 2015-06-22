#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "File.h"
#include <vector>
#include <string>
using namespace std;

class Directory: public File
{
public:
    // c'tor
    Directory(string name, File* parent = NULL);

    // d'tor
    ~Directory();

    //*********************************************************************************************
    //* Name:           AddFile
    //* Description:    Add a new file to the directory, the file will be added at the end of the 
    //*                 files list
    //* Parameters:     File* file - a pointer of the file to be added
    //* Return value:   bool - true if the file was added successfully 
    //*                        false if a file with the same name already exists in the directory
    //*********************************************************************************************
    bool AddFile(File* pFile);

    //*********************************************************************************************
    //* Name:           print
    //* Description:    Print the directory to the screen
    //* Parameters:     None
    //* Return value:   None
    //* Output example:
    //* Directory:
    //*     Name: /root/dir2
    //*     Files: file1 file2
    //*********************************************************************************************
    void print() const;


    //*********************************************************************************************
    //* Name:           RemoveFile
    //* Description:    Remove a file from the directory
    //* Parameters:     string file_name - a of the file to remove
    //* Return value:   bool - true if the file was removed successfully
    //*                        false if a file with the same name doesn't exist in the directory
    //*********************************************************************************************
    bool RemoveFile(string file_name);

    //*********************************************************************************************
    //* Name:           GetNumOfFiles
    //* Description:    returns number of files in the directory
    //* Parameters:    	none
    //* Return value:   int - num of files.
    //*********************************************************************************************
    int GetNumOfFiles() const;


    //*********************************************************************************************
    //* Name:           GetFile
    //* Description:    returns pointer to file/
    //* Parameters:    	string file_name - name of the file we are searching for
    //* Return value:   File* pointer to file.
    //*********************************************************************************************
    File* GetFile(string file_name);

    //*********************************************************************************************
    //* Name:           operator==
    //* Description:    Implements the equality operator
    //* Parameters:     File file - the file to compare against
    //* Return value:   bool - true if both files are the same, false otherwise
    //*********************************************************************************************
    bool operator==(const File& file) const;


    // Need to define the iterator as friend to give it access to some of our members
    friend class FilesIterator;

    //*********************************************************************************************
    //* Name:           begin
    //* Description:    Returns a new iterator to the begining of the subtree starting from the 
    //*                 current directory, where the current directory is the first element
    //* Parameters:     None
    //* Return value:   FilesIterator - a new iterator that can traverse the file system tree
    //*********************************************************************************************
    FilesIterator begin();

    //*********************************************************************************************
    //* Name:           end
    //* Description:    Returns a new iterator pointing to an invalid element representing the end 
    //*                 of the file system tree
    //* Parameters:     None
    //* Return value:   FilesIterator - a new dummy iterator to the end of the file system tree 
    //*********************************************************************************************
    FilesIterator end();

    // TODO: Add your code here...

protected:
    vector<File*> m_files;
};

#endif
