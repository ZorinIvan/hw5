#include "File.h"
#include "FilesIterator.h"
#include "Directory.h"

#include <iterator>
#include <vector>
#include <stack>

//*********************************************************************************************
//* Name:           operator++ (prefix)
//* Description:    Implements the prefix increment operator (++it)
//*                 Addvane the iterator to the next element and returns it's new value
//* Parameters:     None
//* Return value:   FilesIterator - the iterator itself after it was advanced by one element
//*********************************************************************************************
FilesIterator& FilesIterator::operator++()
{
    // First we need to check if we are in a directory or not
    Directory *pDir = dynamic_cast<Directory*>(m_pFile);

    // If we are in a directory and we still have unvisited files, go down one level in the tree
    if( (NULL != pDir) && (m_currentIndex < pDir->m_files.size()) )
    {
        m_pFile = pDir->m_files[m_currentIndex];
        
        // Save the next file to be visited in the current directory in the stack
        m_stack.push(m_currentIndex + 1);
        m_currentIndex = 0;

        return *this;
    }
    else
    {
        // While the stack is not empty
        while( !m_stack.empty() )
        {
            // Go up one level
            m_pFile = m_pFile->m_parent;
            pDir = dynamic_cast<Directory*>(m_pFile);

            // Retrive the current index from the stack
            m_currentIndex = m_stack.top();
            m_stack.pop();

            // If we have unvisited files in this level, go down one level in the tree
            if( m_currentIndex < pDir->m_files.size() )
            {
                m_pFile = pDir->m_files[m_currentIndex];

                // Save the next file to be visited in the current directory in the stack
                m_stack.push(m_currentIndex + 1);
                m_currentIndex = 0;

                return *this;
            }
        }

        // If we finished the stack and didn't fine any unvisited file, we're done
        if( m_stack.empty() )
        {
            // Set the iterator to point to the end of the tree
            m_pFile = NULL;
            m_currentIndex = 0;
            return *this;
        }
    }

    return *this;
}

// TODO: Add your code here...
