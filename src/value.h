#pragma once
#include "main.h"

#define SHABLON '$'

class Value {
private:
	string name;
	string value;

public:
	Value() {

	}

	string getName() {
		return name;
	}

	string getValue() {
		return value;
	}
	string setValue(string value, vector<Value>& vals) {
		this->value = value;
		parseValue(vals);
	}
	Value(string name, string value) {
		this->name = name;
		if (value != "") {
			int i = 0;
			while (value[i] == '\t' && i < value.length()) ++i;
			this->value = "";
			for (; i < value.length(); ++i) {
				this->value += value[i];
			}
		}
	}


	void parseValue(vector<Value>& vals, int i = 0) {
		Value::parseStr(this->value, vals);
	}
	static void parseStr(string& value, vector<Value> vals, int i = 0) {
		while (i < value.length()) {
			Value tmp;
			if (value[i] == SHABLON) {
				tmp = getVal(value, vals, i + 1);
				value.erase(i, tmp.name.length() + 2);
				int j = tmp.value.length() - 1;
				while (tmp.value[j] == '\n') {
					--j;
				}
				tmp.value[j + 1] = '\0'; //erase \n, that was at shablon
				value.insert(i, tmp.value);
				i += tmp.value.length();
			}
			++i;
		}
	}
	
	static Value getVal(string str, vector<Value>& vals,int i = 0) {
		string name = "";
		while (str[i] != '$') {
			name += str[i++];
		}
		for (int i = 0; i < vals.size(); ++i) {
			if (vals[i].name == name)
				return vals[i];
		}
		return Value();
	}
};
