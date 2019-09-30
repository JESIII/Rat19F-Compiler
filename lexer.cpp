//John Scales
//323 Project 1
//Lexical analyzer

#include <iostream>
#include <fstream>
using namespace std;
fstream rat, icg;
char c;
string buff;
string seperators[] = { "%%", ")", "(", ";", "{", "}", "[*", "*]","," };
string operators[] = { "+", "-", "/", "*", "=", "==", "<=", ">=", "!=", "/=", "<", ">" };
string keywords[] = { "real", "int", "function", "if", "fi",
"while", "return", "get", "put", "otherwise", "boolean", "true", "false" };
void FSMsep(){

}
void FSMop(){

}
void FSMid(){
	bool keyfound = false;
	int i = 1;
	while (isalpha(c) || isdigit(c) || c == '_'){
		rat.get(c);
		buff[i] = c;
		i++;
	}
	for (string key : keywords){
		if (buff.substr(0,i) == key){
			cout << buff.substr(0,i) << "	Keyword" << endl;
			keyfound = true;
			rat.putback(c);
		}
	}
	if (!keyfound){
		cout << buff.substr(0,i) << "	Identifier" << endl;
		rat.putback(c);
	}
}

void FSMintreal(){
	int i = 1;
	while (isdigit(c)){
		rat.get(c);
		buff[i] = c;
		i++;
	}
	if (c == '.'){
		do{
			rat.get(c);
			i++;
			buff[i] = c;
		} while (isdigit(c));
		cout << buff.substr(0,i) << "	Real" << endl;
		rat.putback(c);
	}
	else if (!isdigit(c) && c != '.'){
		cout << buff.substr(0,i) << "	Integer" << endl;
		rat.putback(c);
	}
}

int main()
{
	rat.open("C:/Users/tinco/Dropbox (CSU Fullerton)/323/Project 1/sample.rat19");
	if (rat.is_open()) cout << "source code open.\n";
	icg.open("C:/Users/tinco/Dropbox (CSU Fullerton)/323/Project 1/icg.rat19");
	if (icg.is_open()) cout << "file to write open.\n";
	string test = "testing123";
	cout << test.substr(0, 4) << endl;
	while(rat.get(c)){
		buff[0] = c;

		for (string op : operators){
			if (buff.substr(0,1) == op){
				rat.get(c);
				buff[1] = c;
				if (buff.substr(0,2) == op){
					cout << buff.substr(0,2) << "	Operator" << endl;
				}
				else{
					cout << buff.substr(0,1) << "	Operator" << endl;
					rat.putback(c);
				}
			}
		}
		for (string sep : seperators){
			if (buff.substr(0,1) == sep){
				rat.get(c);
				buff[1] = c;
				if (buff.substr(0,2) == sep){
					cout << buff.substr(0,2) << "	Seperator" << endl;
					rat.putback(c);
				}
				else {
					cout << buff[0] << "	Seperator" << endl;
					rat.putback(c);
				}
			}
		}
		if (isalpha(c)){
			FSMid();
		}
		if (isdigit(c)){
			FSMintreal();
		}
	}
}
//NEED TO INCRREMENT i
