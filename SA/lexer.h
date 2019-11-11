#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <string.h>
using namespace std;
ofstream fout("./output.txt");
ifstream fin("../Lexer/Test-Cases/sample.rat19");
char ch2;
char ch;
string keyword;
string identifier;
string number;
//=========================================================================
// Function to check if a key value matches a value in an array
//=========================================================================
bool in_array(char key, char* arr, int size) {
	for (int i = 0; i < size; i++) {
		if (key == arr[i]) {
			return true;
		}
	}
	return false;
}
//=========================================================================a
// Function to check if a number integer or a real number
//=========================================================================
string getNumOrReal(char number) {

	//====================================================================
	//Finite state machine that can tell if int or real number or invalid
	// States:
	//		1 - Integer
	//		2 - Real
	//		3 - Invalid
	//====================================================================
	int finiteStateMachine[4][3] = {
				/*Initial State 0*/{1, 3, 3},
				/*State 1*/		     {1, 2, 3},
				/*State 2*/        {2, 3, 3},
				/*State 3*/		     {3, 3, 3}
									};


	//====================================================================
	// Pointer keeping track of position in finite state machine
	// Starts at State 1 because we already know the first char is a number
	//====================================================================
	int position = 1;

	char buf[100];
	buf[0] = number;
	int index = 1;

	char nextChar;
	while (nextChar = fin.peek()) {
		if (isdigit(nextChar)) {
			position = finiteStateMachine[position][0];
		}
		else if (nextChar == '.') {
			position = finiteStateMachine[position][1];
		}
		else {
			position = finiteStateMachine[position][2];
		}

		if (position == 3) {
			buf[index] = '\0';
			break;
		}
		else {
			buf[index++] = nextChar;
		}
		fin.get();
	}
	return buf;
}

string isKeyword(char buffer[]) {
	string keywords[14] = { "real", "int", "function", "if", "fi", "for", "while", "return", "get", "put", "otherwise", "boolean", "true", "false" };
	int i, flag = 0;

	for (i = 0; i < 14; ++i) {
		if (strcmp(keywords[i].c_str(), buffer) == 0) {
			return keywords[i];
		}
	}
	return "-1";
}

string Lexer() {
	if (!fin.is_open()) {
		cout << "error while opening the file\n";
		exit(0);
	}
	while (ch != ' ' || ch != '\n'){
		ch = fin.get();
		char operators[8]= { '+', '-', '/', '*', '=', '<', '!' };
		char seperators[10] = { '%', ')', '(', ';', '{', '}', '[', ',', ']', '*' };

		if (isalpha(ch)) {
			int finiteStateMachine[4][3] = {
						/*Initial State 0*/{1, 3, 3},
						/*State 1 id*/		 {1, 2, 3},
						/*State 2 key*/		 {2, 3, 3},
						/*State 3 inv*/		 {3, 3, 3}
			};
			int index = 0;
			char identifier[100];
			identifier[0] = ch;
			ch2 = fin.peek();
			while (isalnum(ch2) || ch2 == '_') {
				index++;
				identifier[index] = ch2;
				fin.get();
				ch2 = fin.peek();
			}
			identifier[++index] = '\0';
			keyword = isKeyword(identifier);
			if (keyword != "-1") {
				cout << "Token: keyword" <<" Lexeme: "<< keyword << endl;
				//fout << keyword << " keyword\n";
				return "keyword";
			}
			else {
				cout << "Token: identifier " << "Lexeme: " << identifier << endl;
				//fout << identifier << " identifier\n";
				return "identifier";
			}
		}

		else if (isdigit(ch)) {
			number = getNumOrReal(ch);
			if (number.find(".") != -1) {
				cout <<  "Token: real " << "Lexeme: "<< number <<endl;
				//fout << number << " real\n";
				return "real";
			}
			else {
				cout <<  "Token: integer " << "Lexeme: "<< number <<endl;
				fout << number << " integer\n";
				return "integer";
			}
		}

		else if (in_array(ch, seperators, 10)) {
			ch2 = fin.peek();
			if (ch2 == '%') {
				cout <<  "Token: seperator " << "Lexeme: "<< ch << ch2 <<endl;
				//fout << ch << ch2 << " seperator\n";
				fin.get();
				return "seperator";
			}
			else if (ch2 == ']') { //handles *]
				cout << ch << ch2 << " seperator\n";
				fout << ch << ch2 << " seperator\n";
				fin.get();
				return "seperator";
			}
			else if (ch2 == '*') { //handles [*
				cout << ch << ch2 << " seperator\n";
				fout << ch << ch2 << " seperator\n";
				fin.get();
				char seeker;
				while(seeker != '*'){
					fin.get(seeker);
				}
				fin.unget();
				return "seperator";
			}
			else if (ch == '*'){ //Since * can be an operator or beginning of sep, we need this to handle it being an op.
				cout << ch << " operator\n";
				fout << ch << " operator\n";
				return "operator";
			}
			else {
				cout << ch << " seperator\n";
				fout << ch << " seperator\n";
				return "seperator";
			}
		}

		else if (in_array(ch, operators, 8)) {
			ch2 = fin.peek();
			if (ch2 == '>') {
				cout << ch << ch2 << " operator\n";
				fout << ch << ch2 << " operator\n";
				fin.get();
				return "operator";
			}
			else if (ch2 == '=') {
				cout << ch << ch2 << " operator\n";
				fout << ch << ch2 << " operator\n";
				fin.get();
				return "operator";
			}
			else {
				cout << ch << " operator\n";
				fout << ch << " operator\n";
				return "operator";
			}
		}
	}
	//fout.close();
  //fin.close();
	return "$";
}
void LexerDone(){
	fin.close();
}
