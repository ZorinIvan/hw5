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

/*Constructor*/
FilesIterator::FilesIterator(File* root) : m_pFile(root), m_currentIndex(0)
{
	stack<int> m_stack;
}

FilesIterator::FilesIterator(const FilesIterator& fit) /*Probably is incorrect*/
{
	m_stack = fit.m_stack;
	m_pFile = fit.m_pFile; /*Might be incorrect - when we delete fit it will be deleted*/
	m_currentIndex = fit.m_currentIndex;
}

bool FilesIterator::operator==(const FilesIterator& rhs)
{
	if (rhs.m_currentIndex == m_currentIndex && rhs.m_stack == m_stack && rhs.m_pFile == m_pFile)
		return true;
	else
		return false;
}

bool FilesIterator::operator!=(const FilesIterator& rhs)
{
	return !(operator==(rhs)); /*Return the opposite than ==*/
}

File& FilesIterator::operator*()
{
	return *m_pFile;
}

File* FilesIterator::operator->()
{
	return m_pFile;
}
