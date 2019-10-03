#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<ctype.h>
#include <string>

using namespace std;

bool in_array(char key, char buffer[]) {
	for (int i = 0; i < sizeof(buffer) / 4; i++) {
		if (key == buffer[i]) {
			return true;
		}
	}
	return false;
}

int isKeyword(char buffer[]) {
	char keywords[32][10] = { "real", "int", "function", "if", "fi",
"while", "return", "get", "put", "otherwise", "boolean", "true", "false" };
	int i, flag = 0;

	for (i = 0; i < 32; ++i) {
		if (strcmp(keywords[i], buffer) == 0) {
			flag = 1;
			break;
		}
	}

	return flag;
}
int isOperator(char buffer[]) {
	char operators[8] = { '+', '-', '/', '*', '=', '<', '>', '!' };
	int i, flag = 0;
	for (i = 0; i < 8; ++i) {
		if (in_array(operators[i],buffer)) {
			flag = operators[i] == '=' ? 2 : 1;
			flag = operators[i] == '<' ? 3 : 1;
			flag = operators[i] == '>' ? 4 : 1;
			flag = operators[i] == '!' ? 5 : 1;
			break;
		}
	}
	return flag;
}
int isSeperator(char buffer[]) {
	char seperators[9] = { '%', ')', '(', ';', '{', '}', '[', ',', ']' };
	int i, flag = 0;
	for (i = 0; i < 9; ++i) {
		if (in_array(seperators[i], buffer)) {
			flag = seperators[i] == '%' ? 2 : 1;
			flag = seperators[i] == '*' ? 3 : 1;
			flag = seperators[i] == '[' ? 4 : 1;
			break;
		}
	}
	return flag;
}
/*
int isIntReal(char buffer[]) {

	int i, flag = 0;

	for (i = 0; i < 32; ++i) {
		if (strcmp(keywords[i], buffer) == 0) {
			flag = 1;
			break;
		}
	}

	return flag;
}
*/

int main() {
	char ch, buffer[20];
	ifstream fin("C:/Users/tinco/Dropbox (CSU Fullerton)/323/Project 1/sample.rat19");
	int i, j = 0;

	if (!fin.is_open()) {
		cout << "error while opening the file\n";
		exit(0);
	}
	while (!fin.eof()) {
		ch = fin.get();
		char operators[8]= { '+', '-', '/', '*', '=', '<', '>', '!' };
		char seperators[9] = { '%', ')', '(', ';', '{', '}', '[', ',', ']' };
		bool foundsep = false;
		for (i = 0; i < 9; ++i) {
			if (ch == seperators[i]) {
				buffer[j] = ch;
				int temp = isSeperator(buffer);
				if (temp == 1) {
					buffer[++j] = '\0';
					cout << buffer << " is seperator\n";
					j = 0;
				}
				else if (temp == 2) {
					char next = fin.peek();
					if (next == '%') {
						buffer[++j] = fin.get();
						buffer[++j] = '\0';
						cout << buffer << " is seperator\n";
						j = 0;
					}
				}
				else if (temp == 3) {
					char next = fin.peek();
					if (next == ']') {
						buffer[++j] = fin.get();
						buffer[++j] = '\0';
						cout << buffer << " is seperator\n";
						j = 0;
					}
				}
				else if (temp == 4) {
					char next = fin.peek();
					if (next == '*') {
						buffer[++j] = fin.get();
						buffer[++j] = '\0';
						cout << buffer << " is seperator\n";
						j = 0;
					}
				}
				else {
					cout << ch << " is seperator\n";
				}
				foundsep = true;
			}
		}

		for (i = 0; i < 8; ++i) {
			if (ch == operators[i] && foundsep == false) {
				buffer[j] = ch;
				int temp = isOperator(buffer);
				if (temp > 0 ) {
					char next = fin.peek();
					if (next == '=') {
						buffer[++j] = fin.get();
						buffer[++j] = '\0';
						cout << buffer << " is operator\n";
						j = 0;
					}
				}
				else {
					cout << ch << " is operator\n";
				}
			}
		}
		if (isalnum(ch)) {
			buffer[j++] = ch;
		}
		else if ((ch == ' ' || ch == '\n') && (j != 0)) {
			buffer[j] = '\0';
			j = 0;

			if (isKeyword(buffer) == 1)
				cout << buffer << " is keyword\n";
			else
				cout << buffer << " is indentifier\n";
		}

	}

	fin.close();

	return 0;
}
