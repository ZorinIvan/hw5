#ifndef FILES_ITERATOR_H
#define FILES_ITERATOR_H

#include "File.h"
#include "Directory.h"

#include <iterator>
#include <stack>

class FilesIterator: public iterator<forward_iterator_tag, File>
{
public:
    // c'tor
    FilesIterator(File* root);

    // copy c'tor
    FilesIterator(const FilesIterator& fit);

    //*********************************************************************************************
    //* Name:           operator++ (prefix)
    //* Description:    Implements the prefix increment operator (++it)
    //*                 Addvane the iterator to the next element and returns it's new value
    //* Parameters:     None
    //* Return value:   FilesIterator - the iterator itself after it was advanced by one element
    //*********************************************************************************************
    FilesIterator& operator++();

    //*********************************************************************************************
    //* Name:           operator++ (suffix)
    //* Description:    Implements the suffix increment operator (it++)
    //*                 Addvane the iterator to the next element and returns it's value before the 
    //*                 operation
    //* Parameters:     int - a dummy parameter to distinguish between prefix and suffix increment,
    //*                       the parameter value itself is ignored
    //* Return value:   FilesIterator - the iterator itself after it was advanced by one element
    //*********************************************************************************************
    FilesIterator operator++(int)
    {
        FilesIterator tmp(*this);
        operator++();
        return tmp;
    }

    //*********************************************************************************************
    //* Name:           operator==
    //* Description:    Implements the equality operator
    //* Parameters:     FilesIterator rhs - the file iterator to compare against
    //* Return value:   bool - true if both files iterators are the same, false otherwise
    //*********************************************************************************************
    bool operator==(const FilesIterator& rhs);

    //*********************************************************************************************
    //* Name:           operator!=
    //* Description:    Implements the non-equality operator
    //* Parameters:     FilesIterator rhs - the file iterator to compare against
    //* Return value:   bool - true if both files iterators are different, false otherwise
    //*********************************************************************************************
    bool operator!=(const FilesIterator& rhs);

    //*********************************************************************************************
    //* Name:           operator*
    //* Description:    Implements the pointer derefrencing operator (*it)
    //* Parameters:     None
    //* Return value:   File& - a reference to the current element that the iterator is pointing at
    //*********************************************************************************************
    File& operator*();

    //*********************************************************************************************
    //* Name:           operator->
    //* Description:    Implements the structure derefrencing operator (it->)
    //* Parameters:     None
    //* Return value:   File* - a pointer to the current element that the iterator is pointing at
    //*********************************************************************************************
    File* operator->();

private:
    // Keep a stack of visited locations in the tree in order to keep track of the next file 
    // that needs to be visited
    stack<int> m_stack;

    // A pointer to the file that we are currently pointing at
    File* m_pFile;

    // Our location in the file list in the current directory
    unsigned int m_currentIndex;
};

#endif
