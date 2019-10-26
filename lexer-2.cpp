#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <string.h>
#include <lexer-2.h>

using namespace std;

ifstream fin("./sample.rat19");
ofstream fout("./output.txt");
enum idkey{KY,ID,RL,IN,SEP,OP};

int main() {

	if (!fin.is_open()) {
		cout << "error while opening the file\n";
		exit(0);
		}

	char operators[8]= { '+', '-', '/', '*', '=', '<', '>', '!' };
	char seperators[10] = { '%', ')', '(', ';', '{', '}', '[', ',', ']', '*' };
	int finiteStateMachine[4][3] = {
			/*Initial State 0*/	{1, 3, 3},
			/*State 1 id*/		{1, 2, 3},
			/*State 2 key*/		{2, 3, 3},
			/*State 3 inv*/		{3, 3, 3}
			};
	char ch;
	string idk[]={"keyword","identifier","real number","integer", "seperator", "operator"};
	string k;
	idkey i;

	while (!fin.eof()) {
		ch = fin.get();
		i = chew(fin,ch,k,operators,seperators,finiteStateMachine);
		//do actions with id and strig, for now just print
		cout << k << " is a " << idk[i] << endl;
		fout << k << " is a " << idk[i] << endl;
	}// end while
	fout.close();
	fin.close();

	return 0;
}