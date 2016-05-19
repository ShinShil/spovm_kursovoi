#pragma once
#include "main.h"
#include "file.h"
#include "folder.h"
#include <Windows.h>
#include "Errors.h"
#include "Service.h"

class FileSystem {
private:
	string currentPath;
	int maxNameSize = 255;
public:
	FileSystem(string currentPath) {
		this->currentPath = currentPath;
	}
	static void createFile(string path) {
		HANDLE hFile = CreateFile(path.c_str(), GENERIC_ALL, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
		if (!hFile) {
			path += " doesn't created";
			Errors::printError("create file", path);
		}
		CloseHandle(hFile);
	}
	
	static void createFolder(string name) {
		if (!CreateDirectory(name.c_str(), NULL)) {
			name += " doesn't created";
			Errors::printError("create directory", name);
		}
	}
	static void copyFile(string src, string dest) {
		if (CopyFile(src.c_str(), dest.c_str(), TRUE) == FALSE) {
			string message = "fail to copy file: " + src;
			Errors::printError("copyFile", message);
			cout << Service::getLastError()<<endl;
		}
	}
	static File* findFile(string name, string dir) {
		FileSystem fs(dir);
		vector<File*> files = fs.getFiles();
		vector<File*>::iterator beg = files.begin();
		while (beg != files.end()) {
			if (name == (*beg)->getName()) {
				return (*beg);
			}
			++beg;
		}
		return NULL;
	}
	static string getNameFromFullName(string fullName) {
		int i = fullName.length() - 1;
		string res = "";
		while (fullName[i] != '/' && fullName[i] != '\\' && i > 0) {
			--i;
		}
		++i; //miss the '/'
		for (; i < fullName.length(); ++i) {
			res += fullName[i];
		}
		return res;
	}

	static int getPos(string fileName, string str) {
		File file(fileName);
		string qwe = file.getContent();
		int res = qwe.find(str);
		return res;
		
	}



	static void insertToFile(string fullName, string str, int pos) {
		ofstream ofs;
		try {
			File* file = new File(fullName);
			string tmp = file->getContent();
			tmp.insert(pos, str);
			ofs.open(fullName.c_str(), std::ios::out);
			if (!ofs)
				throw new FileOpenException(fullName);
			//гостинная красоты: шуры-муры, Елена
			ofs << tmp;
			ofs.close();
			
		}
		catch (FileOpenException ex) {
			ex.printError();
			if (ofs.is_open())
				ofs.close();
		}
		return;
	}

	static void writeToFile(string fullName, string content) {
		ofstream ofs;
		try {
			ofs.open(fullName.c_str(), ios_base::app);
			if (!ofs)
				throw new FileOpenException(fullName);
			ofs << content;
			ofs.close();
		}
		catch(FileOpenException ex) {
			ex.printError();
			if (ofs.is_open())
				ofs.close();
		}
		return;
	}
	static void copyDir(string srcRef, string destRef) {
		//for pTo and pFrom - strings must be ended with "\0\0"
		string src;
		string dest;
		string pattern;
		HANDLE hFile;
		WIN32_FIND_DATA findFileData;

		pattern = srcRef + "\\*";

		//create dest dir
		if (CreateDirectory(destRef.c_str(), NULL) == FALSE) {
			string message = "fail to create Directory: " + destRef;
			Errors::printError("copyDir", message);
			return;
		}

		//copy files
		hFile = FindFirstFile(pattern.c_str(), &findFileData);
		if (hFile == INVALID_HANDLE_VALUE) {
			string message = "fail to find first file: " + pattern;
			Errors::printError("copyDir", message);
			return;
		}

		do {
			if (findFileData.cFileName[0] != '.') {
				dest.erase();
				src.erase();
				dest = destRef;
				dest += "\\";
				dest += findFileData.cFileName;
				src = srcRef;
				src += "\\";
				src += findFileData.cFileName;

				if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					copyDir(src, dest);
				}
				else {
					if (CopyFile(src.c_str(), dest.c_str(), TRUE) == FALSE) {
						string message = "fail to copy file: " + src;
						Errors::printError("copyDir", message);
						return;
					}
				}
			}
		} while (FindNextFile(hFile, &findFileData));
	}
	vector<File*> getFiles() {
		vector<File*> res;
		char* currDir = new char[maxNameSize + 1];
		char* debug = new char[maxNameSize + 1];
		string currFindPath = currentPath + "\\*";

		GetCurrentDirectory(maxNameSize, currDir);
		SetCurrentDirectory(currentPath.c_str());
		WIN32_FIND_DATA findFileData;
		HANDLE hSearch;
		BOOL hFinished = FALSE;
		
		hSearch = FindFirstFile(currFindPath.c_str(), &findFileData);
		if (hSearch == INVALID_HANDLE_VALUE)
			return res;
		else {
			do {
				File* tmp = new File(currentPath + "\\" + findFileData.cFileName, findFileData.cFileName, currentPath + "");
				res.push_back(tmp);
			} while (FindNextFile(hSearch, &findFileData));
		}

		SetCurrentDirectory(currDir);
		this->currentPath = currDir;
		delete[] currDir;
		return res;
	}
	void cd(string arg) {

	}

	static void setCurrDir(string str) {
		SetCurrentDirectory(str.c_str());
	}

	void setPath(string newPath) {

	}
	static string getCurrDir() {
		char* str = new char[MAX_NAME_SIZE - 1];
		GetCurrentDirectory(MAX_NAME_SIZE, str);
		string res = str;
		return res;
	}
};
