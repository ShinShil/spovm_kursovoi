#pragma once
#include "main.h"
#include "file.h"
#include "Service.h"
#include "fileSystem.h"
#include "value.h"
#include "insert.h"

#define END_COMMAND ';'


class TaskParser {
private:
	static vector<string> tokens;
	vector<Value> vals; //variables
	vector<string> commandLineArgs;
	vector<Insert> inserts;
	File* file;
	string content;

	string getToken(int& i) { //first word should be token or variable
		//getWord - if it token, return
		string res = "";
		stack<int> bracers;
		while (content[i] != ' ' && content[i] != '\0') {
			if (content[i] != '\n' && content[i] != ';')
				res += content[i];
			++i;
		}
		vector<string>::iterator beg = tokens.begin();
		while (beg != tokens.end()) {
			if (*beg++ == res)
				break;
		}
		//++i; //miss the END_COMMAND
		return res;
	}
	string getArgs(int& i) {
		string res = "";
		stack<int> bracers;
		while (content[i] != END_COMMAND || !bracers.empty()) {
			if (content[i] == '{') {
				bracers.push(1);
			}
			if (content[i] == '}') {
				bracers.pop();
			}
			res += content[i];
			++i;
		}
		return res;
	}
	//tokens functions
	void caseCreateFile(vector<string> args) {
		vector<string>::iterator beg = args.begin();
		while (beg != args.end()) {
			string obj = FileSystem::getCurrDir() + "\\" + *beg;
			FileSystem::createFile(obj);
			++beg;
		}
	}
	void caseCreateFolder(vector<string> args) {
		vector<string>::iterator beg = args.begin();
		while (beg != args.end()) {
			string obj = FileSystem::getCurrDir() + "\\" + *beg;
			FileSystem::createFolder(obj);
			++beg;
		}
	}
	void caseCopyFolder(vector<string> args) {
		vector<string>::iterator beg = args.begin();
		while (beg != args.end()) {
			string src = file->getDir() + "\\" + *beg;
			string dest = FileSystem::getCurrDir() + "\\" + *beg;
			FileSystem::copyDir(src, dest);
			++beg;
		}
	}
	void caseCopyFile(vector<string> args) {
		vector<string>::iterator beg = args.begin();
		while (beg != args.end()) {

			string src;
			if (Service::strContain(*beg, '\\') || Service::strContain(*beg, '/')) {
				string fileName = FileSystem::getNameFromFullName(*beg);
				File* findFile = FileSystem::findFile(fileName, file->getDir());
				if (findFile != NULL)
					src = findFile->getFullName();
				else {
					string message = *beg + " not found";
					Errors::printError("caseCopyFile", message);
				}
			}
			else {
				src = file->getDir() + "\\" + *beg;
			}
			string dest = FileSystem::getCurrDir() + "\\" + *beg;
			FileSystem::copyFile(src, dest);
			++beg;
		}
	}
	void caseParams(vector<string> args) {
		int amount = args.size() > commandLineArgs.size() ? args.size() : commandLineArgs.size();
		for (int i = 0; i < amount; ++i) {
			vals.push_back(Value(args[i], commandLineArgs[i]));
		}
		for (int i = 0; i < amount; ++i) {
			vals[i].parseValue(vals);
		}
	}
	void caseWriteToFile(vector<string> args) {
		//0 - file
		//1,2,.. - code
		string fullName = FileSystem::getCurrDir() + "\\" + args[0];
		for (int i = 1; i < args.size(); ++i) {
			FileSystem::writeToFile(fullName, args[i]);
		}
	}
	void caseVal(vector<string> args) {
		//0 - valName
		//1,2,... - values, if more than one - concatenate
		vals.push_back(Value(args[0], args[1]));
		vals[vals.size() - 1].parseValue(vals);
	}
	void caseInsertToFile(vector<string> args) {
		//0 - fileName
		//1 - insert type arg
		for (int i = 1; i < args.size(); ++i) {
			for (int j = 0; j < inserts.size(); ++j) {
				if (args[i] == inserts[j].getName()) {
					inserts[j].run(FileSystem::getCurrDir() + "\\" + args[0]);
				}
			}
		}
	}

	void caseInsert(vector<string> args) {
		inserts.push_back(Insert(args[0], args[1]));
		Value::parseStr(inserts[inserts.size() - 1].getBody(), vals);
	}

public:
	TaskParser(File* file, vector<string> commandLineArgs) {
		this->file = file;
		this->commandLineArgs = commandLineArgs;
	}
	void run() {
		int i = 0;
		content = file->getContent();
		while (true) {
			string token = getToken(i);
			if ((UINT)i >= content.length() - 1)
				break;
			string argString = getArgs(i);
			vector<string> args = Service::split(argString);

			//if args is value - replace it
			//if args contains vals - replace it

			for (int i = 0; i < args.size(); ++i) {
				Value::parseStr(args[i], vals);
				for (int j = 0; j < vals.size(); ++j) {
					if (args[i] == vals[j].getName()) {
						args[i] = vals[j].getValue();
					}
				}
			}
			
			if (token == "createFile") {
				caseCreateFile(args);
				continue;
			}
			if (token == "createFolder") {
				caseCreateFolder(args);
				continue;
			}
			if (token == "copyFolder") {
				caseCopyFolder(args);
				continue;
			}
			if (token == "copyFile") {
				caseCopyFile(args);
				continue;
			}
			if (token == "params") {
				caseParams(args);
				continue;
			}
			if (token == "writeToFile") {
				caseWriteToFile(args);
				continue;
			}
			if (token == "val") {
				caseVal(args);
			}
			if (token == "insertToFile") {
				caseInsertToFile(args);
			}
			if (token == "insert") {
				caseInsert(args);
			}
		}
	}
};

vector<string> TaskParser::tokens = {
	"createFile",
	"createFolder",
	"copyFolder",
	"copyFile",
	"params",
	"writeToFile",
	"val",
	"insertToFile",
	"insert"
};