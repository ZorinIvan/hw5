#include "TextFile.h"
#include <string>
#include <iostream>

using namespace std;

//constructor
TextFile::TextFile(string name, File* parent, string text)
	:File(name, parent), text(text){}

void TextFile::print() const{
	cout<<"Name: "<<getfullName()<<endl; //print path+file name
	cout<<"Text: "<<text<<endl;
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

