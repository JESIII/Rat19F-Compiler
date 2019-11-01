#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <string.h>

using namespace std;

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
// Function to check if a number is an integer or a real number
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
				/*Initial State 0*/	 {1, 3, 3},
				/*State 1*/		 {1, 2, 3},
				/*State 2*/		 {2, 3, 3},
				/*State 3*/		 {3, 3, 3}
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

idkey chew(ifstream& fin, char ch, string &st, int (&op)[8], int (&sep)[10], int (&fsm)[4][3]){
//replace all "is a foobah" w/ return values, cout/fout will be handled in main

		if (isalpha(ch)) {
			int index = 0;
			char identifier[100];
			identifier[0] = ch;
			char next = fin.peek();
			while (isalnum(next) || next == '_') {
				index++;
				identifier[index] = next;
				fin.get();
				next = fin.peek();
			}
			identifier[++index] = '\0';
			string keyword = isKeyword(identifier);
			if (keyword != "-1") {
				//set st to keyword, return enum for keyword
				st = keyword;//this works for ref strings right
				return KY;
			}
			else {
				st = keyword;
				return ID;
			}
		}//if ch

		else if (isdigit(ch)) {
			string number = getNumOrReal(ch);
			if (number.find(".") != -1) {
				st = keyword;
				return RL;
			}
			else {
				st = keyword;
				return IN;
			}
		}//else ch

		else if (in_array(ch, seperators, 10)) {
			char next = fin.peek();
			if (next == '%') {
				st = keyword;
				fin.get();
				return SEP;
			}
			else if (next == ']') { //handles *]
				st = keyword;
				fin.get();
				return SEP;
			}
			else if (next == '*') { //handles [*
				st = keyword;
				fin.get();
				return SEP;
			}
			else if (ch == '*'){ //Since * can be an operator or beginning of sep, we need this to handle it being an op.
				st = keyword;
				return OP;
			}
			else {
				st = keyword;
				return SEP;
			}
		}//e

		else if (in_array(ch, operators, 8)) {
			char next = fin.peek();
			if (next == '=') {
				st = keyword;
				fin.get();
				return OP;
			}
			else {
				st = keyword;
				return OP;
			}
		}
