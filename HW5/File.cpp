#include "File.h"
#include <string>

using namespace std;

//Constructor]
File::File(string name, File* parent)
	: m_name(name), m_parent(parent){}

string File::getName() const{
	return m_name;
}

string File::getPath() const{
	return m_path;
}

//returns file name+space+path
string File::getfullName() const{
	string full_name;
	full_name=m_name + ' ' + m_path;
	return full_name;
}

File* File::getParrent() const{
	return m_parent;
}


