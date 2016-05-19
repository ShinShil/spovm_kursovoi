#pragma once
#include "main.h"

#define MAX_NAME_SIZE 256

class File {
private:
	string fullName;
	string name;
	string dir;
	ifstream* ifs;
public:
	File(string path, string name = "", string dir = "") {
		this->fullName = path;
		this->name = name;
		this->dir = dir;
		
	}
	string getContent() {
		string content = "";
		ifstream* ifs = new ifstream();
		try {
			ifs->open(fullName);
			if (!ifs)
				throw FileOpenException(fullName);
			while (ifs->good()) {
				char* tmp = new char[MAX_NAME_SIZE + 1];
				ifs->getline(tmp, MAX_NAME_SIZE);
				content += tmp;
				content += "\n"; //as getline() not add it the tmp, need to do it manually
			}
			ifs->close();
		}
		catch (FileOpenException ex) {
			ex.printError();
			if (ifs->is_open())
				ifs->close();
			content = "error";
		}
		return content;
	}
	int setContent(string content) {
		ofstream ofs;
		int res = SUCCESS;
		try {
			ofs.open(fullName);
			if (!ofs)
				throw FileOpenException(fullName);
			ofs << content;
			ofs.close();
		}
		catch (FileOpenException ex) {
			ex.printError();
			if (ofs.is_open())
				ofs.close();
			res = FAIL;
		}
		return content.length();
	}
	string getDir() {
		return this->dir;
	}
	string getName() {
		return name;
	}
	string getFullName() {
		return fullName;
	}
	File& operator=(const File& other) {
		
		ifs = new ifstream();
		this->fullName = other.fullName;
		this->dir = other.dir;
		this->name = other.name;
		return *this;
	}

};