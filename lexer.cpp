#include <iostream>
#include <fstream>
#include <vector>
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
		for (string j : seperators) {
			for (string k : operators) {
				for (string l : keywords) {
					if (buffer.substr(0,i) == j) {
						icg.write(buffer.c_str(), i);
						icg << endl;
						i = 0;
						buffer.clear();
					}
					else if (buffer.substr(0, i) == k){
						buffer[i + 1] = rat.get();
						if (buffer.substr(0, i+1) == "==") {
							icg.write(buffer.c_str(), i+1);
							icg << endl;
						}
						else if (buffer.substr(0, i + 1) == "<=") {
							icg.write(buffer.c_str(), i + 1);
							icg << endl;
						}
						else if (buffer.substr(0, i + 1) == ">=") {
							icg.write(buffer.c_str(), i + 1);
							icg << endl;
						}
						else if (buffer.substr(0, i + 1) == "!=") {
							icg.write(buffer.c_str(), i + 1);
							icg << endl;
						}
						else if (buffer.substr(0, i + 1) == "/=") {
							icg.write(buffer.c_str(), i + 1);
							icg << endl;
						}
						else {
							rat.unget();
							icg.write(buffer.c_str(), i);
							icg << endl;
						}
						i = 0;
						buffer.clear();
					}
					else if (buffer.substr(0, i) == l || rat.get() == ' ') {
						icg.write(buffer.c_str(), i);
						icg << endl;
						i = 0;
						buffer.clear();
					}
					i++;
				}
			}
		}
	}
}
