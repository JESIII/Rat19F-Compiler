#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <string.h>
//#include "lexer.h"
using namespace std;
ofstream fout("./output.txt");
ifstream fin("../Lexer/Test-Cases/sample.rat19");
char ch2;
char ch;
string ch3;
string keyword;
string identifier;
string number;
void CC();
bool BB();
bool AA();
bool ZPrime();
bool Z();
bool YPrime();
bool Y();
bool X();
bool W();
bool V();
bool U();
bool T();
bool S();
bool R();
bool Q();
bool P();
bool O();
bool N();
bool M();
bool L();
bool K();
bool J();
bool I();
bool H();
bool G();
bool F();
bool E();
bool D();
bool C();
bool B();
bool A();
bool APrime();

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
				cout << "Token: keyword" <<"           Lexeme: "<< keyword << endl;
				//fout << keyword << " keyword\n";
				return "keyword";
			}
			else {
				cout << "Token: identifier " << "          Lexeme: " << identifier << endl;
				//fout << identifier << " identifier\n";
				return "identifier";
			}
		}

		else if (isdigit(ch)) {
			number = getNumOrReal(ch);
			if (number.find(".") != -1) {
				cout <<  "Token: real " << "          Lexeme: "<< number <<endl;
				//fout << number << " real\n";
				return "real";
			}
			else {
				cout <<  "Token: integer " << "          Lexeme: "<< number <<endl;
				fout << number << " integer\n";
				return "integer";
			}
		}

		else if (in_array(ch, seperators, 10)) {
			ch2 = fin.peek();
			if (ch2 == '%') {
				cout <<  "Token: seperator " << "          Lexeme: "<< ch << ch2 <<endl;
				//fout << ch << ch2 << " seperator\n";
				fin.get();
				return "seperator";
			}
			else if (ch2 == ']') { //handles *]
				cout <<  "Token: seperator " << "          Lexeme: "<< ch << ch2 <<endl;
				//fout << ch << ch2 << " seperator\n";
				fin.get();
				return "seperator";
			}
			else if (ch2 == '*') { //handles [*
				cout <<  "Token: seperator " << "          Lexeme: "<< ch << ch2 <<endl;
				//fout << ch << ch2 << " seperator\n";
				fin.get();
				char seeker;
				while(seeker != '*'){
					fin.get(seeker);
				}
				fin.unget();
				return "seperator";
			}
			else if (ch == '*'){ //Since * can be an operator or beginning of sep, we need this to handle it being an op.
				cout <<  "Token: operator " << "          Lexeme: "<< ch <<endl;
				//fout << ch << " operator\n";
				return "operator";
			}
			else {
				cout <<  "Token: seperator " << "          Lexeme: "<< ch <<endl;
				//fout << ch << " seperator\n";
				return "seperator";
			}
		}

		else if (in_array(ch, operators, 8)) {
			ch2 = fin.peek();
			if (ch2 == '>') {
				cout <<  "Token: operator " << "          Lexeme: "<< ch << ch2 <<endl;
				//fout << ch << ch2 << " operator\n";
				fin.get();
				return "operator";
			}
			else if (ch2 == '=') {
				cout <<  "Token: operator " << "          Lexeme: "<< ch << ch2 <<endl;
				//fout << ch << ch2 << " operator\n";
				fin.get();
				return "operator";
			}
			else {
				cout <<  "Token: operator " << "          Lexeme: "<< ch <<endl;
				//fout << ch << " operator\n";
				return "operator";
			}
		}
	}
	//fout.close();
  //fin.close();
  cout << "hmm";
	return "$";
}
void LexerDone(){
	fin.close();
}
//Beginning of rules
bool APrime(){//the rule that augments the grammar. Just calls A. Not sure if it needs to check anything.
  if (A()){
    return true;
  }
  return false;
}
///////////////////////////////////////
bool A(){
  ch3 = ch + ch2;
  if(B()){
    if(Lexer() == "seperator" && ch3 == "%%"){
      if(J()){
        if(N()){
          if(Lexer() == "seperator" && ch3 == "%%"){
            return true;
          }
        }
      }
    }
  }
  return false;
}
///////////////////////////////////////
bool B(){
  if(C()){
    return true;
  }
  else{
    CC();
  }
  return false;
}
///////////////////////////////////////
bool C(){
  if(D()){
    return true;
  }
  else if (D()){
    if(C()){
      return true;
    }
  }
  return false;
}
///////////////////////////////////////
bool D(){
  if (Lexer() == "keyword" && keyword == "function"){
    if (Lexer() == "identifier"){
      if (Lexer() == "seperator" && ch == '('){
        if (E()){
          if (Lexer() == "seperator" && ch == ')'){
            if(J()){
              if(I()){
                return true;
              }
            }
          }
        }
      }
    }
  }
  return false;
}
///////////////////////////////////////
bool E(){
  if(F()){
    return true;
  }
  else{
    CC();
  }
  return false;
}
///////////////////////////////////////
bool F(){
  if(G()){
    return true;
  }
  else if(G()){
    if(Lexer() == "seperator" && ch == ','){
      if(F()){
        return true;
      }
    }
  }
  return false;
}
///////////////////////////////////////
bool G(){
  if (M()){
    if (H()){
      return true;
    }
  }
  return false;
}
///////////////////////////////////////
bool H(){
  if (Lexer() == "integer"){
    return true;
  }
  else if (Lexer() == "keyword" && (keyword == "true" || keyword == "false")){
    return true;
  }
  return false;
}
///////////////////////////////////////
bool I(){
  if(Lexer() == "seperator" && ch == '{'){
    if(N()){
      if(Lexer() == "seperator" && ch == '}'){
        return true;
      }
    }
  }
  return false;
}
///////////////////////////////////////
bool J(){
  if(K()){
    return true;
  }
  else {
    CC();
  }
  return false;
}
///////////////////////////////////////
bool K(){
  if(L()){
    if(Lexer() == "seperator" && ch == ';'){
      return true;
    }
  }
  else if(L()){
    if(Lexer() == "seperator" && ch == ';'){
      if(K()){
        return true;
      }
    }
  }
  return false;
}
///////////////////////////////////////
bool L(){
  if(H()){
    if(M()){
      return true;
    }
  }
  return false;
}
///////////////////////////////////////
bool M(){
  if(Lexer()=="identifier"){
    return true;
  }
  else if(Lexer() == "identifier"){
    if(Lexer() == "seperator" && ch == ','){
      if (M()){
        return true;
      }
    }
  }
  return false;
}
///////////////////////////////////////
bool N(){
  if(O()){
    cout << "<Statement>   "<<endl;
    return true;
  }
  else if(O()){
    if(N()){
      cout << "<Statement> <Statement List>"<<endl;
      return true;
    }
  }
  return false;
}
///////////////////////////////////////
bool O(){
  if(P()){
    cout << "<Compound> "<<endl;
    return true;
  }
  else if(Q()){
    cout << "<Assign>   "<<endl;
    return true;
  }
  else if(R()){
    cout << "<If>   "<<endl;
    return true;
  }
  else if(S()){
    cout << "<Return>      "<<endl;
    return true;
  }
  else if(T()){
    cout << "<Print>       "<<endl;
    return true;
  }
  else if(U()){
    cout << "<Scan>     "<<endl;
    return true;
  }
  else if(V()){
    cout << "<While> "<<endl;
    return true;
  }
  return false;
}
///////////////////////////////////////
bool P(){
  if(Lexer() == "seperator" && ch == '{'){
    if (N()){
      if(Lexer() == "seperator" && ch == '}'){
        cout << "{  <Statement List>  } "<<endl;
        return true;
      }
    }
  }
  return false;
}
///////////////////////////////////////
bool Q(){
  if (Lexer() == "identifier"){
    if(Lexer() == "seperator" && ch == '='){
      if(Y()){
        if(Lexer() == "seperator" && ch == ';'){
          cout << "<Identifier> = <Expression> ;"<<endl;
          return true;
        }
      }
    }
  }
  return false;
}
///////////////////////////////////////
bool R(){
  if(Lexer() == "keyword" && keyword == "if"){
    if(Lexer() == "seperator" && ch == '('){
      if(W()){
        if(Lexer() == "seperator" && ch == ')'){
          if(O()){
            if(Lexer() == "keyword" && keyword == "fi"){
              cout << "if  ( <Condition>  ) <Statement>   fi" << endl;
              return true;
            }
          }
        }
      }
    }
  }
  else if(Lexer() == "keyword" && keyword == "if"){
    if(Lexer() == "seperator" && ch == '('){
      if(W()){
        if(Lexer() == "seperator" && ch == ')'){
          if(O()){
            if(Lexer() == "keyword" && keyword == "otherwise"){
              if(O()){
                if(Lexer() == "keyword" && keyword == "fi"){
                  cout << "if  ( <Condition>  ) <Statement>   otherwise  <Statement>  fi " << endl;
                  return true;
                }
              }
            }
          }
        }
      }
    }
  }
  return false;
}
///////////////////////////////////////
bool S(){
  if(Lexer() == "keyword" && keyword == "return"){
    if (Lexer() == "seperator" && ch == ';'){
      cout << "return ; "<< endl;
      return true;
    }
  }
  else if (Lexer() == "keyword" && keyword == "return"){
    if(Y()){
      if (Lexer() == "seperator" && ch == ';'){
        cout << "return <Expression> ;"<<endl;
        return true;
      }
    }
  }
  return false;
}
///////////////////////////////////////
bool T(){
  if(Lexer() == "keyword" && keyword == "put"){
    if(Lexer() == "seperator" && ch == '('){
      if (Y()){
        if (Lexer() == "seperator" && ch == ')'){
          cout << "put ( <Expression>);" << endl;
          return true;
        }
      }
    }
  }
  return false;
}
///////////////////////////////////////
bool U(){
  if(Lexer() == "keyword" && keyword == "get"){
    if(Lexer() == "seperator" && ch == '('){
      if (M()){
        if (Lexer() == "seperator" && ch == ')'){
          cout << "get ( <IDs> );" << endl;
          return true;
        }
      }
    }
  }
  return false;
}
///////////////////////////////////////
bool V(){
  if(Lexer() == "keyword" && keyword == "while"){
    if(Lexer() == "seperator" && ch == '('){
      if (W()){
        if (Lexer() == "seperator" && ch == ')'){
          if(O()){
            cout << "<While> ::=  while ( <Condition> ) <Statement>" << endl;
            return true;
          }
        }
      }
    }
  }
  return false;
}
///////////////////////////////////////
bool W(){
  if(Y()){
    if(X()){
      if(Y()){
        cout << "<Condition> ::=     <Expression>  <Relop>   <Expression>"<<endl;
        return true;
      }
    }
  }
  return false;
}
///////////////////////////////////////
bool X(){
  ch3 = ch + ch2;
  if (Lexer() == "operator" && ch3 == "=="){

    return true;
  }
  return false;
}
///////////////////////////////////////
bool Y(){
  if(Z()){
    if(YPrime()){
      return true;
    }
  }
  return false;
}
///////////////////////////////////////
bool YPrime(){
  if (Lexer() == "operator" && ch == '+'){
    if(Z()){
      if(YPrime()){
        return true;
      }
    }
  }
  else if (Lexer() == "operator" && ch == '-'){
    if(Z()){
      if(YPrime()){
        return true;
      }
    }
  }
  else{
    CC();
  }
  return false;
}
///////////////////////////////////////
bool Z(){
  if(AA()){
    if(ZPrime()){
      return true;
    }
  }
  return false;
}
///////////////////////////////////////
bool ZPrime(){
  if(Lexer() == "operator" && ch == '*'){
    if(AA()){
      if(ZPrime()){
        return true;
      }
    }
  }
  else if(Lexer() == "operator" && ch == '/'){
    if(AA()){
      if(ZPrime()){
        return true;
      }
    }
  }
  else{
    CC();
  }
  return false;
}
///////////////////////////////////////
bool AA(){
  if(Lexer() == "operator" && ch == '-'){
    if(BB()){
      return true;
    }
  }
  else if (BB()){
    return true;
  }
  return false;
}
///////////////////////////////////////
bool BB(){
  if(Lexer() == "identifier"){
    return true;
  }
  else if(Lexer() == "integer"){
    return true;
  }
  else if(Lexer() == "identifier"){
    if(Lexer() == "seperator" && ch == '('){
      if (M()){
        if (Lexer() == "seperator" && ch == ')'){
          return true;
        }
      }
    }
  }
  else if(Lexer() == "seperator" && ch == '('){
    if (Y()){
      if (Lexer() == "seperator" && ch == ')'){
        return true;
      }
    }
  }
  else if(Lexer() == "real"){
    return true;
  }
  else if(Lexer() == "keyword" && (keyword == "true" || keyword == "false")){
    return true;
  }
  return false;
}
///////////////////////////////////////
void CC(){
  LexerDone();
}
///////////////////////////////////////
int main(){
  if(APrime()){
    cout << "Parsing complete.";
  }
}
