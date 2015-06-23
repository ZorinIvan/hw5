#include "Directory.h"
#include <string>
#include <iostream>
#include "FilesIterator.h"

using namespace std;


// constructor
Directory::Directory(string name, File* parent)
	:File(name, parent){}

//copy constructor
Directory::Directory(const Directory& obj )
	:File(obj.m_name, obj.m_parent){
	for(unsigned int i=0; i<obj.m_files.size();i++){
		m_files[i]=obj.m_files[i];
	}
}


// destructor
Directory::~Directory(){
	for (unsigned int i = 0; i<(int)m_files.size(); i++){
		delete m_files[i];
	}
}

bool Directory::AddFile(File* pFile){
	/*check if the file already exists*/
	for (unsigned int i = 0; i<m_files.size(); i++){

		//??????????????????????????????
		if(m_files[i]==pFile) //overloading operator "=="
			return false;//file with the same name already exists in this directory
	}

	m_files.push_back(pFile); //add pointer to the end of vector
	return true;
}

void Directory::print() const{

	cout<<"Directory:"<<endl;
	cout<<"\tName: "<<getfullName()<<endl; //print path+dir name
	cout<<"\tFiles: ";
	for(int i=0; i<m_files.size(); i++ ){ //print all file names in the dir
		cout<<m_files[i]->getName()<<" ";
	}
	cout<<endl;
}


bool Directory::RemoveFile(string file_name){
	if(m_files.size()==0) //nothing to remove
		return false;
	for (unsigned int i = 0; i<m_files.size(); i++){
		if(m_files[i]->getName()==file_name){
			delete m_files[i]; //??????????????????
			m_files.erase(m_files.begin()+i);
			return true;
		}
	}
	return false; //file not found
}

int Directory::GetNumOfFiles() const{
	return (int)m_files.size();
}

File* Directory::GetFile(string file_name){
	if(m_files.size()==0)
		return NULL; //empty vector
	for (unsigned int i = 0; i<m_files.size(); i++){
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
	while (current.operator->() != NULL) /*We want to return the invalid item that gives us null file*/
	{
		//FilesIterator memory(current);
		++current;
		//if (current.operator->() == NULL)
			//return memory;
	}
	return current;
}

string Directory::getPath() const
{
	return getfullName();
}
