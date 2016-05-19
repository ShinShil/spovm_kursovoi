#pragma once
#include "main.h"
#include <stack>
class Service {
public:
	static void parseInsert(vector<string>& inserts, vector<string>& codes, string str) {
		int i = 0;
		string tmp = "";
		while (i < str.length() && str[i] != '\0') {
			if (str[i] == '[') {
				inserts.push_back(getLineInBracers(str, i, '[', ']'));
				++i;
				if (tmp != "") {
					codes.push_back(tmp);
					tmp = "";
				}
				continue;
			}
			tmp += str[i++]; //++i - so we check the next symbol
		}
		if (tmp != "")
			codes.push_back(tmp);
	}
	static string getLineInBracers(string str, int& i, char open = '{', char close = '}') {
		string res = "";
		stack<int> stack;
		if (str[i] == open) {
			stack.push(1);
			++i;
		}
		while (!stack.empty()) {
			if (str[i] == open)
				stack.push(1);
			if (str[i] == close)
				stack.pop();
			if (stack.empty())
				return res;
			res += str[i++];
		}
		return "";
	}
	static string getCodeArg(string str, int& i) {
		string res = "";
		stack<int> stack;
		if (str[i] == '{') {
			stack.push(1);
			i+=2; //to remove '{' and after it '\n'
		}
		while (!stack.empty()) {
			if (str[i] == '{') {
				stack.push(1);
			}
			if (str[i] == '}') {
				stack.pop();
			}
			if (!stack.empty()) {
				res += str[i];
			} else {
				++i; // for erasing '\n' after '}'
			}
			++i;
		}
		return res;
	}
	static int findFirst(string src, string str) {

	}
	static vector<string> split(string line) {
		vector<string> result;
		stack<int> bracers;
		int i = 0;
		while (line[i] == ' ') {
			++i;
		}
		string tmp = "";
		while (i<line.length() && line[i] != '\0') {
			if (line[i] == '{') {
				result.push_back(getCodeArg(line, i));
				continue;
			}
			if (line[i] != ' ') {
				tmp += line[i];
			}
			else {
				if (tmp != "") {
					result.push_back(tmp);
					tmp = "";
				}
			}
			++i;
		}
		if (tmp != "")
			result.push_back(tmp);
		return result;
	}

	static int getLastError() {
		return GetLastError();
	}
	static BOOL strContain(string str, char ch) {
		string::iterator beg = str.begin();
		while (beg != str.end()) {
			if (*beg++ == ch)
				return TRUE;
		}
		return FALSE;
	}
};
