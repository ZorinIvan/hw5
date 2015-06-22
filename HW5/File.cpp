#include "File.h"
#include <string>

using namespace std;

//Constructor]
File::File(string name, File* parent)
	: m_name(name), m_parent(parent){
	if(parent==NULL)
		m_path="/";
	else
		m_path=parent->getfullName();
}

string File::getName() const{
	return m_name;
}

string File::getPath() const{
	return m_path;
}

//returns file name+space+path
string File::getfullName() const{
	string full_name;
	if(m_path=="/")
		full_name=m_path+m_name;
	else
		full_name=m_path+'/'+m_name;
	return full_name;
}

File* File::getParrent() const{
	return m_parent;
}


/*Tesing*/
