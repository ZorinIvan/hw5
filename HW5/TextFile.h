#ifndef TEXT_FILE_H
#define TEXT_FILE_H

#include "File.h"
#include <string>
using namespace std;

class TextFile: public File
{
public:
    // c'tor
    TextFile(string name, File* parent = NULL, string text = "");

    //*********************************************************************************************
    //* Name:            print
    //* Description:    Print the text file to the screen
    //* Parameters:     None
    //* Return value:   None
    //* Output example:
    //* Text file:
    //*     Name: /root/dir2/file3
    //*     Text: "test"
    //*********************************************************************************************
    void print() const;

    // TODO: Add your code here...

private:
    // TODO: Add your code here...
};

#endif
