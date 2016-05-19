#include "main.h"
#include "commandAnalyser.h"

int main(int argc, char* argv[]) {


	vector<string> args;
	/*
	args.push_back("add");
	args.push_back("test.txt");
	*/
/*
	args.push_back("testJava");
	args.push_back("Fire");
	args.push_back("Fire");

	string str = "C:\\AAAA1111\\univer\\spovm_kursovoi\\testProject";

	FileSystem::setCurrDir(str);*/
	cout << endl << FileSystem::getCurrDir()<<endl;
	
	for (int i = 1; i < argc; ++i) {
		args.push_back(argv[i]);
	}

	CommandAnalyser commandAnalyze;
	commandAnalyze.analyze(args);

	cout << endl;
	system("pause");
	return 0;
}