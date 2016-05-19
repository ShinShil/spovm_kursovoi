#pragma once
#include <string>
#include <iostream>
using namespace std;

class Errors {
public:
	static void printError(std::string error, std::string message) {
		std::cout << "\nError \"" << error << "\":" << message;
	}
};

class BaseError {
public:
	virtual void printError() = 0;
};

class FileOpenException: public BaseError {
private:
	string filePath;
public:
	FileOpenException(string filePath) {
		this->filePath = filePath;
	}
	void printError() {
		cout << "\nError file open, file: \"" << filePath << "\"";
	}
};