#pragma once
#include "main.h"
#include "Errors.h"
#include <fstream>
#include "fileSystem.h"


class TaskDirsFile {
private:
	string file;
	vector<string>dirs;
	int max_name_size;
	ifstream ifs;
	ofstream ofs;
public:
	TaskDirsFile(string file) {
		this->file = file;
		try {
			ifs.open(file.c_str());
			if (!ifs)
				throw FileOpenException(file);
			max_name_size = 256;
			while (ifs.good()) {
				char* tmp = new char[max_name_size + 1];
				ifs.getline(tmp, max_name_size);
				dirs.push_back(tmp);
			}
			ifs.close();
		}
		catch(FileOpenException ex) {
			ex.printError();
			if(ifs.is_open())
				ifs.close();
		}
	}

	void printDirs() {
		cout << "\nTask directories list\n\n";
		vector<string>::iterator beg = dirs.begin();
		while (beg != dirs.end()) {
			cout << *beg++<<endl;
		}
	}

	void set(string path) {
		dirs.clear();
		dirs.push_back(path);
		try {
			ofs.open(file.c_str());
			if (!ofs)
				throw new FileOpenException(file);
			ofs.clear();
			ofs << path << "\n";
		}
		catch (FileOpenException ex) {
			ex.printError();
			if (ofs.is_open())
				ofs.close();
		}
	}
	vector<string> getTaskDirs() {
		return dirs;
	}
	void add(string path) {
		dirs.push_back(path);
		try {
			ofs.open(file.c_str(), ios_base::app);
			if (!ofs)
				throw new FileOpenException(file);
			ofs << path << "\n";
		}
		catch (FileOpenException ex) {
			ex.printError();
			if (ofs.is_open())
				ofs.close();
		}
	}
	int findTask(string fileName, File& file) {
		int res = NOT_FOUND;
		fileName += EXTENSION;
		vector<string>::iterator beg = dirs.begin();
		while (beg != dirs.end()) {
			FileSystem folder(*beg);
			vector<File*> files = folder.getFiles();
			vector<File*>::iterator filesBeg = files.begin();
			while (filesBeg != files.end()) {
				if ((*filesBeg)->getName() == fileName) {
					res = FOUND;
					file = **filesBeg;
					break;
				}
				++filesBeg;
			}
			++beg;
		}
		return res;
	}
};
