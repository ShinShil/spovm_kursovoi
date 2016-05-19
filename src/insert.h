#pragma once
#include "value.h"
#include "main.h"

class Insert {
private:
	string name;
	string body;
	static vector<string> tokens;
public:
	Insert(string name, string body) {
		this->name = name;
		this->body = body;
	}
	string getBody() {
		return body;
	}
	void append(string object, string strInserted, string fullFileName) {
		File file(fullFileName);
		string content = file.getContent();
		int pos = content.find(object);
		while (content[pos] != '{') ++pos;
		Service::getLineInBracers(content, pos);
		--pos;
		content.insert(pos, strInserted);
		file.setContent(content);
	}

	void run(string fullFileName) {
		int i = 0;
		string token = "";
		while (body[i] == ' ' || body[i] == '\t') ++i;
		while (body[i] != ' ' && body[i] != '{') {
			token += body[i];
			++i;
		}
		while (body[i] != '{') ++i;
		if (token == "append") {
			string arg1 = Service::getLineInBracers(body, i);
			while (body[i] != '{') ++i;
			string arg2 = Service::getLineInBracers(body, i);
			this->append(arg1, arg2, fullFileName);
		}
	}
	string getName() {
		return name;
	}

};

vector<string> Insert::tokens = {
	"append"
};