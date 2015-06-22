#include "Directory.h"
#include <string>
#include <iostream>
#include "FilesIterator.h"

using namespace std;


// constructor
Directory::Directory(string name, File* parent)
	:File(name, parent){}

// destructor
Directory::~Directory(){
	for(int i=0; i<m_files.size(); i++){
	m_files[i]->~File();
	}
}

bool Directory::AddFile(File* pFile){
	/*check if the file already exists*/
	for(int i=0; i<m_files.size(); i++){

		//??????????????????????????????
		if(m_files[i]==pFile) //overloading operator "=="
			return false;//file with the same name already exists in this directory
	}

	m_files.push_back(pFile); //add pointer to the end of vector
	return true;
}

void Directory::print() const{
	cout<<"Name: "<<getfullName()<<endl; //print path+dir name
	cout<<"Files: ";
	for(int i=0; i<m_files.size(); i++ ){ //print all file names in the dir
		cout<<m_files[i]->getName()<<" ";
	}
	cout<<endl;
}


bool Directory::RemoveFile(string file_name){
	if(m_files.size()==0) //nothing to remove
		return false;
	for(int i=0; i<m_files.size(); i++ ){
		if(m_files[i]->getName()==file_name){
			delete m_files[i]; //??????????????????
			m_files.erase(m_files.begin()+i);
			return true;
		}
	}
	return false; //file not found
}

int Directory::GetNumOfFiles() const{
	return m_files.size;
}

File* Directory::GetFileByName(string file_name){
	if(m_files.size()==0)
		return NULL; //empty vector
	for(int i=0; i<m_files.size(); i++){
		if(m_files[i]->getName()==file_name)
			return m_files[i];
	}
	return NULL;
}

bool Directory::operator==(const File& file) const{
	if(this->getfullName()==file.getfullName()) //check equity of two strings
		return true; //true
	return false; //false
}

FilesIterator Directory::begin()
{ 
	FilesIterator root(this); /*This directory is our start*/
	return root;
}

FilesIterator Directory::end()
{
	FilesIterator current(this);
	while (current.operator-> != NULL) /*We want to return the invalid item that gives us null file*/
	{
		++current;
	}
	return current;
}
