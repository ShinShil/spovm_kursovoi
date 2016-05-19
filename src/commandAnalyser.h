#pragma once
#include "main.h"
#include "Errors.h"
#include "taskDirsFile.h"
#include "fileSystem.h"
#include "taskParser.h"

#define COMMAND_TOKEN 0
#define FIRST_ARG_TOKEN 1

class CommandAnalyser {
private:
	string commandLine;
	vector<string> commands;
	vector<string> argsTaskParser;
	TaskDirsFile* taskDirsFile;
	vector<string> availableCommands;
	void initTaskDirs() {
		availableCommands.push_back("set");
		availableCommands.push_back("add");
		availableCommands.push_back("help");
	}


	void setCase() {
		//args - "filePath", remove all and set one newPath
		try {
			taskDirsFile->set(commands.at(FIRST_ARG_TOKEN));
		}
		catch (std::out_of_range) {
			Errors::printError("input", "wrong params");
		}
	}
	void caseAdd() {
		//args - filePathes, it will be added to taskDirsFile's list
		int i = FIRST_ARG_TOKEN;
		try {
			taskDirsFile->add(commands.at(i));
			++i;
		}
		catch (std::out_of_range) {
			if(i == FIRST_ARG_TOKEN)
				Errors::printError("input", "wrong params");
		}
	}
	void caseHelp() {
		cout << "\nHelp COming soon" << endl;
		for (int i = 0; i < availableCommands.size(); ++i) {
			cout << "\t" << availableCommands[i] << endl;
		}
	}
	void caseCommandList() {
		CommandAnalyser::initTaskDirs();
		cout << "Program: lr; CommandList\n\n";
		std::vector<string>::iterator beg = CommandAnalyser::availableCommands.begin();
		while (beg != availableCommands.end()) {
			cout << *beg++ << endl;
		}
	}
	void caseTaskDirs() {
		taskDirsFile->printDirs();
	}
	
	int findTask(string fileName, File& file) {
		//in each taskDir try to find the the file "fileName" with extension .cpj(defined in main.h)
		return taskDirsFile->findTask(fileName, file);
	}

	void caseTask(File file) {
		TaskParser taskParser(&file, argsTaskParser);
		taskParser.run();
	}
public:
	CommandAnalyser() {
		taskDirsFile = new TaskDirsFile("C:\\AAAA1111\\univer\\spovm_kursovoi\\spovm_kursovoi\\Debug\\taskDirs.txt");
	}

	void analyze(vector<string> commands) {
		if (!commands.size()) {
			caseCommandList();
			return;
		}

		this->commands = commands;
		if (commands[COMMAND_TOKEN] == "set") {
			setCase();
			return;
		}
		if (commands[COMMAND_TOKEN] == "help") {
			caseHelp();
			return;
		}
		if (commands[COMMAND_TOKEN] == "add") {
			caseAdd();
			return;
		}
		if (commands[COMMAND_TOKEN] == "taskDirs") {
			caseTaskDirs();
			return;
		}
		File file("", "", "");
		if (findTask(commands[COMMAND_TOKEN], file)) {
			for (int i = 1; i < commands.size(); ++i) {
				argsTaskParser.push_back(commands[i]);
			}
			caseTask(file);
			return;
		}
		Errors::printError(*(commands.begin()), "no such command, see help");
	}
	void analyze(string commandLine) {
		this->commands = Service::split(commandLine);
		analyze(this->commands);
	}
};
