#ifndef FILE_H
#define FILE_H

#include <string>
using namespace std;

// Forward declation of files iterator
class FilesIterator;

class File
{
public:
    // c'tor
    File(string name, File* parent = NULL);

    // d'tor
    virtual ~File() {}

    //*********************************************************************************************
    //* Name:           getName
    //* Description:    Returns file name 
    //* Parameters:     None
    //* Return value:   string - the file name
    //*********************************************************************************************
    virtual string getName() const;

    //*********************************************************************************************
    //* Name:           getPath
    //* Description:    Returns file path in the file system 
    //* Parameters:     None
    //* Return value:   string - the file path
    //*********************************************************************************************
    virtual string getPath() const;

    //*********************************************************************************************
    //* Name:           getfullName
    //* Description:    Returns the file's name including it's path in the file system
    //* Parameters:     None
    //* Return value:   string - file's full name
    //*********************************************************************************************
    virtual string getfullName() const;

    //*********************************************************************************************
    //* Name:           getParrent
    //* Description:    Returns a pointer to the file's parent in the file system
    //* Parameters:     None
    //* Return value:   string - file's full name
    //*********************************************************************************************
    virtual File* getParrent() const;

    //*********************************************************************************************
    //* Name:           operator==
    //* Description:    Implements the equality operator
    //* Parameters:     File file - the file to compare against
    //* Return value:   bool - true if both files are the same, false otherwise
    //*********************************************************************************************
    virtual bool operator==(const File& file) const = 0;

    //*********************************************************************************************
    //* Name:           print
    //* Description:    Print the file to the screen, the print format depends on the file's type
    //* Parameters:     None
    //* Return value:   None
    //*********************************************************************************************
    virtual void print() const = 0;

    // Need to define the iterator as friend to give it access to some of our members
    friend class FilesIterator;

protected:
    // The file's name
    string m_name;

    // The file's path in the file system
    string m_path;

    // A pointer to the file's parent in the file system
    File* m_parent;
};

#endif
