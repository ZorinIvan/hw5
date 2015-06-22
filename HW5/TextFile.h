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

    //cc'tor
    TextFile(TextFile obj);

    //*********************************************************************************************
    //* Name:            print
    //* Description:    Print the text file to the screen
    //* Parameters:     None
    //* Return value:   None
    //* Output example:
    //* Text file:
    //* 	Name: /root/dir2/file3
    //*     Text: "test"
    //*********************************************************************************************
    void print() const;

    //*********************************************************************************************
    //* Name:           operator==
    //* Description:    Implements the equality operator
    //* Parameters:     File file - the file to compare against
    //* Return value:   bool - true if both files are the same, false otherwise
    //*********************************************************************************************
    bool operator==(const File& file) const;

    //*********************************************************************************************
    //* Name:          	getText
    //* Description:    returns text in the file
    //* Parameters:     none
    //* Return value:   string - text in the file
    //****************************************************************************************
    string getText() const;

    //*********************************************************************************************
    //* Name:          	AddText
    //* Description:    adds text to a current file
    //* Parameters:     string new_text - text that will be added to a current one
    //* Return value:   none
    //****************************************************************************************
    void addText(string new_text);

    //*********************************************************************************************
    //* Name:          	updateText
    //* Description:    changes text in the file to a new one
    //* Parameters:     string new_text - a value that a field "text" will be changed to
    //* Return value:   none
    //****************************************************************************************
    void updateText(string new_text);

private:
    string text;
};

#endif
