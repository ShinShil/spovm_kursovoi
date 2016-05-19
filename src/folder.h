#pragma once
#include "main.h"
#include "file.h"

class Folder {
private:
	string path;
public:
	Folder(string path) {
		this->path = path;
	}
	vector<File>	getFiles() {
		
	}
	vector<Folder>	getFolders() {

	}

	vector<string>	getAll() {

	}
};
