#include "TextFile.h"
#include <string>
#include <iostream>

using namespace std;

//constructor
TextFile::TextFile(string name, File* parent, string text)
	:File(name, parent), text(text){}

//cc'tor
TextFile::TextFile(TextFile obj)
	:File(obj.m_name, obj.m_parent), text(obj.text){}

void TextFile::print() const{
	cout<<"Text file:"<<endl;
	cout<<"\tName: "<<getfullName()<<endl; //print path+file name
	cout<<"\tText: "<<text<<endl;
}

bool TextFile::operator==(const File& file) const{
	if(this->getfullName()==file.getfullName()) //check equity of two strings
		return true; //true
	return false; //false
}

string TextFile::getText() const{
	return text;
}

void TextFile::addText(string new_text){
	text=text+new_text;
}

void TextFile::updateText(string new_text){
	text=new_text;
}

