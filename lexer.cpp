#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	fstream rat, icg;
	rat.open("C:/Users/tinco/Dropbox (CSU Fullerton)/323/Project 1/sample.rat19");
	if (rat.is_open()) cout << "source code open.";
	icg.open("C:/Users/tinco/Dropbox (CSU Fullerton)/323/Project 1/icg.rat19");
	if (icg.is_open()) cout << "file to write open.";
	string seperators[] = { "%%", ")", "(", ";", "{", "}", "[*", "*]","," };
	string operators[] = { "+", "-", "/", "*", "=", "==", "<=", ">=", "!=", "/=", "<", ">" };
	string keywords[] = { "real", "int", "function", "if", "fi",
	"while", "return", "get", "put", "otherwise", "boolean", "true", "false" };
	char single;
	string buffer;
	int i = 0;
	while (rat.get(single)) {
		cout << single;
		buffer[i] = single;
		for (string sep : seperators) {
			for (string op : operators) {
				for (string key : keywords) {
					if (buffer.substr(0,i) == sep) {
						icg << substr(0, i);
						icg << endl;
						i = 0;
						buffer.clear();
					}
					else if (buffer.substr(0, i) == op){
						buffer[i + 1] = rat.get();
						if (buffer.substr(0, i + 1) == "==") {
							icg << buffer.substr(0, i + 1);
							icg << endl;
						}
						else if (buffer.substr(0, i + 1) == "<=") {
							icg << buffer.substr(0, i + 1);
							icg << endl;
						}
						else if (buffer.substr(0, i + 1) == ">=") {
							icg << buffer.substr(0, i + 1);
							icg << endl;
						}
						else if (buffer.substr(0, i + 1) == "!=") {
							icg << buffer.substr(0, i + 1);
							icg << endl;
						}
						else if (buffer.substr(0, i + 1) == "/=") {
							icg << buffer.substr(0, i + 1);
							icg << endl;
						}
						else {
							rat.unget();
							icg << buffer.substr(0, i);
							icg << endl;
						}
						i = 0;
						buffer.clear();
					}
					else if (buffer.substr(0, i) == key) {
						icg << buffer.substr(0, i);
						icg << endl;
						i = 0;
						buffer.clear();
					}

				}
			}
		}
	}
}
//NEED TO INCRREMENT i