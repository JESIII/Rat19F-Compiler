#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <cstring>
#include <vector>
using namespace std;
ofstream fout("./output.txt");
ifstream fin("./Test-Cases/sample.rat19");
char ch2;
char ch;
string ch3;
string keyword;
string identifier;
string number;
int lineNumber = 1;
vector<vector<string>> tokens;
int tokenCounter = -1;
void SetTokenCounter(int);
int GetTokenCounter();
vector<string> GetNextToken();
vector<string> GetToken();
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
class ASM_Operation{
	size_t address;
	string op;
	string oprnd;
};
vector<ASM_Operation> instr_table;
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

void SetTokenCounter(int count) {
	tokenCounter = count;
}

int GetTokenCounter() {
	return tokenCounter;
}

vector<string> GetNextToken() {
	tokenCounter++;
	return GetToken();
}

vector<string> GetToken() {
	return tokens.at(tokenCounter);
}


int GetLineNumber() {
	return stoi(GetToken()[2]);
}

int GetLineNumber(int index) {
	return stoi(tokens.at(index)[2]);
}

void Lexer() {
	if (!fin.is_open()) {
		fout << "error while opening the file\n";
		exit(0);
	}
	while (!fin.eof()){
		ch = fin.get();
		if (ch == ' ') {
			continue;
		}
		if (ch == '\n') {
			lineNumber++;
			continue;
		}
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
				tokens.push_back(vector<string>{ "keyword", keyword });
			}
			else {
				tokens.push_back(vector<string>{ "identifier", identifier });
			}
		}

		else if (isdigit(ch)) {
			number = getNumOrReal(ch);
			if (number.find(".") != -1) {
				tokens.push_back(vector<string>{ "real", number });
			}
			else {
				tokens.push_back(vector<string>{ "integer", number });
			}
		}

		else if (in_array(ch, seperators, 10)) {
			ch2 = fin.peek();
			if (ch2 == '%') {
				fin.get();
				tokens.push_back(vector<string>{ "seperator", string() + ch + ch2 });
			}
			else if (ch2 == ']') { //handles *]
				fin.get();
				tokens.push_back(vector<string>{ "seperator", string() + ch + ch2 });
			}
			else if (ch2 == '*') { //handles [*
				char seeker = fin.get();
				while(seeker != ']'){
					fin.get(seeker);
				}
				//fin.unget();
				//tokens.push_back(vector<string>{ "seperator", string() + ch + ch2 });
			}
			else if (ch == '*'){ //Since * can be an operator or beginning of sep, we need this to handle it being an op.
				tokens.push_back(vector<string>{ "operator", string() + ch });
			}
			else {
				tokens.push_back(vector<string>{ "seperator", string() +  ch });
			}
		}

		else if (in_array(ch, operators, 8)) {
			ch2 = fin.peek();
			if (ch2 == '>') {
				fin.get();
				tokens.push_back(vector<string>{ "operator", string() + ch + ch2 });
			}
			else if (ch2 == '=') {
				fin.get();
				tokens.push_back(vector<string>{ "operator", string() + ch + ch2 });
			}
			else {
				tokens.push_back(vector<string>{ "operator", string() + ch });
			}
		}
	}
	//fout.close();
  //fin.close();

  for (unsigned int i = 0; i < tokens.size(); i++) {
	  fout << "Token: "<< tokens.at(i)[0] << "        Lexeme: " << tokens.at(i)[1] << endl;
  }
	fout << "LEXER COMPLETE!" << endl;
  return;
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
  if(B()){
    if(GetNextToken()[0] == "seperator" && GetToken()[1] == "%%"){
      if(J()){
        if(N()){
          if(GetNextToken()[0] == "seperator" && GetToken()[1] == "%%"){
			  fout << "<Rat19F>  ::=   <Opt Function Definitions>   %%  <Opt Declaration List>  <Statement List>  %%" << endl;
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
  int counter = GetTokenCounter();

  if(C()){
	  fout << "<Opt Function Definitions> ::= <Function Definitions> " << endl;
    return true;
  }

  fout << "<Opt Function Definitions> ::= <Empty> " << endl;
  SetTokenCounter(counter);
  return true;
}
///////////////////////////////////////
bool C(){
  if(D()){
	  int counter = GetTokenCounter();
	  if (C()) {
		  fout << "<Function Definitions>  ::= <Function> <Function Definitions>" << endl;
		  return true;
	  }
	  else {
		  fout << "<Function Definitions>  ::= <Function> " << endl;
		  SetTokenCounter(counter);
		  return true;
	  }
  }
  return false;
}
///////////////////////////////////////
bool D(){
  if (GetNextToken()[0] == "keyword" && GetToken()[1] == "function"){
    if (GetNextToken()[0] == "identifier"){
      if (GetNextToken()[0] == "seperator" && GetToken()[1] == "("){
        if (E()){
          if (GetNextToken()[0] == "seperator" && GetToken()[1] == ")"){
            if(J()){
              if(I()){
				  fout << "<Function> ::= function  <Identifier>   ( <Opt Parameter List> )  <Opt Declaration List>  <Body>" << endl;
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
  int counter = GetTokenCounter();

  if(F()){
	fout << "<Opt Parameter List> ::=  <Parameter List>" << endl;
    return true;
  }

  fout << "<Opt Parameter List> ::=  <Empty>" << endl;
  SetTokenCounter(counter);
  return true;
}
///////////////////////////////////////
bool F(){
  if(G()){
	  int counter = GetTokenCounter();
	  if (GetNextToken()[0] == "seperator" && GetToken()[1] == ",") {
		  if (F()) {
			  fout << "<Parameter List>  ::=  <Parameter> , <Parameter List>" << endl;
			  return true;
		  }
	  }
	  else {
		  fout << "<Parameter List>  ::=  <Parameter>" << endl;
		  SetTokenCounter(counter);
		  return true;
	  }
  }
  return false;
}
///////////////////////////////////////
bool G(){
  if (M()){
    if (H()){
	  fout << "<Parameter> ::=  <IDs >  <Qualifier>" << endl;
      return true;
    }
  }
  return false;
}
///////////////////////////////////////
bool H(){
  if (GetNextToken()[0] == "keyword" && (GetToken()[1] == "int" || GetToken()[1] == "boolean" || GetToken()[1] == "real")){
	fout << "<Qualifier> ::= " << GetToken()[1] << endl;
    return true;
  }
  return false;
}
///////////////////////////////////////
bool I(){
  if(GetNextToken()[0] == "seperator" && GetToken()[1] == "{"){
    if(N()){
      if(GetNextToken()[0] == "seperator" && GetToken()[1] == "}"){
		fout << "<Body>  ::=  {  < Statement List>  }" << endl;
        return true;
      }
    }
  }
  return false;
}
///////////////////////////////////////
bool J(){
  int counter = GetTokenCounter();

  if(K()){
	fout << "<Opt Declaration List> ::= <Declaration List>" << endl;
    return true;
  }

  fout << "<Opt Declaration List> ::= <Empty>" << endl;
  SetTokenCounter(counter);
  return true;
}
///////////////////////////////////////
bool K(){
  if(L()){
    if(GetNextToken()[0] == "seperator" && GetToken()[1] == ";"){
		int counter = GetTokenCounter();
		if (K()) {
			fout << "<Declaration List>  := <Declaration> ; <Declaration List>" << endl;
			return true;
		}
		else {
			fout << "<Declaration List>  := <Declaration> ;" << endl;
			SetTokenCounter(counter);
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
	  fout << "<Declaration> ::=   <Qualifier > <IDs>" << endl;
      return true;
    }
  }
  return false;
}
///////////////////////////////////////
bool M(){
  if(GetNextToken()[0] =="identifier"){
	  int counter = GetTokenCounter();
	  if (GetNextToken()[0] == "seperator" && GetToken()[1] == "," && M()) {
		  fout << "<IDs> ::= <Identifier> , <IDs>" << endl;
		  return true;
	  }
	  else {
		  fout << "<IDs> ::= <Identifier>" << endl;
		  SetTokenCounter(counter);
		  return true;
	  }
  }
  return false;
}
///////////////////////////////////////
bool N(){
  if (O()) {
	  int counter = GetTokenCounter();
	  if (N()) {
		  fout << "<Statement List> ::= <Statement> <Statement List>" << endl;
		  return true;
	  }
	  else {
		  SetTokenCounter(counter);
		  fout << "<Statement List> ::= <Statement>" << endl;
		  return true;
	  }
    return true;
  }
  return false;
}
///////////////////////////////////////
bool O(){
  int counter = GetTokenCounter();

  if(P()){
    fout << "<Statement> ::= <Compound>"<<endl;
    return true;
  }

  SetTokenCounter(counter);

  if(Q()){
    fout << "<Statement> ::= <Assign>"<<endl;
    return true;
  }

  SetTokenCounter(counter);

  if(R()){
    fout << "<Statement> ::= <If>"<<endl;
    return true;
  }

  SetTokenCounter(counter);

  if(S()){
    fout << "<Statement> ::= <Return>"<<endl;
    return true;
  }

  SetTokenCounter(counter);

  if(T()){
    fout << "<Statement> ::= <Print>"<<endl;
    return true;
  }

  SetTokenCounter(counter);

  if(U()){
    fout << "<Statement> ::= <Scan>"<<endl;
    return true;
  }

  SetTokenCounter(counter);

  if(V()){
    fout << "<Statement> ::= <While>"<<endl;
    return true;
  }

  return false;
}
///////////////////////////////////////
bool P(){
  if(GetNextToken()[0] == "seperator" && GetToken()[1] == "{"){
    if (N()){
      if(GetNextToken()[0] == "seperator" && GetToken()[1] == "}"){
        fout << "<Compound> ::= {  <Statement List>  } "<<endl;
        return true;
      }
    }
  }
  return false;
}
///////////////////////////////////////
bool Q(){
  if (GetNextToken()[0] == "identifier"){
    if(GetNextToken()[0] == "operator" && GetToken()[1] == "="){
      if(Y()){
        if(GetNextToken()[0] == "seperator" && GetToken()[1] == ";"){
          fout << "<Assign> ::= <Identifier> = <Expression> ;" << endl;
          return true;
        }
      }
    }
  }
  return false;
}
///////////////////////////////////////
bool R(){
  int counter = GetTokenCounter();

  if(GetNextToken()[0] == "keyword" && GetToken()[1] == "if"){
    if(GetNextToken()[0] == "seperator" && GetToken()[1] == "("){
      if(W()){
        if(GetNextToken()[0] == "seperator" && GetToken()[1] == ")"){
          if(O()){
            if(GetNextToken()[0] == "keyword" && GetToken()[1] == "fi"){
              fout << "<If> ::= if ( <Condition> ) <Statement> fi" << endl;
              return true;
            }
          }
        }
      }
    }
  }

  SetTokenCounter(counter);

  if(GetNextToken()[0] == "keyword" && GetToken()[1] == "if"){
    if(GetNextToken()[0] == "seperator" && GetToken()[1] == "("){
      if(W()){
        if(GetNextToken()[0] == "seperator" && GetToken()[1] == ")"){
          if(O()){
            if(GetNextToken()[0] == "keyword" && GetToken()[1] == "otherwise"){
              if(O()){
                if(GetNextToken()[0] == "keyword" && GetToken()[1] == "fi"){
                  fout << "<If> ::= if ( <Condition>  ) <Statement> otherwise <Statement> fi" << endl;
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
	if (GetNextToken()[0] == "keyword" && GetToken()[1] == "return") {
		int counter = GetTokenCounter();
		if (Y()) {
			if (GetNextToken()[0] == "seperator" && GetToken()[1] == ";") {
				fout << "<Return> ::=  return <Expression> ;" << endl;
				return true;
			}
		}

		SetTokenCounter(counter);

		if (GetNextToken()[0] == "seperator" && GetToken()[1] == ";") {
			fout << "<Return> ::= return ;" << endl;
			return true;
		}
	}
  return false;
}
///////////////////////////////////////
bool T(){
  if(GetNextToken()[0] == "keyword" && GetToken()[1] == "put"){
    if(GetNextToken()[0] == "seperator" && GetToken()[1] == "("){
      if (Y()){
        if (GetNextToken()[0] == "seperator" && GetToken()[1] == ")"){
			if (GetNextToken()[0] == "seperator" && GetToken()[1] == ";") {
				fout << "<Print> ::= put ( <Expression> ) ;" << endl;
				return true;
			}
        }
      }
    }
  }
  return false;
}
///////////////////////////////////////
bool U(){
  if(GetNextToken()[0] == "keyword" && GetToken()[1] == "get"){
    if(GetNextToken()[0] == "seperator" && GetToken()[1] == "("){
      if (M()){
        if (GetNextToken()[0] == "seperator" && GetToken()[1] == ")"){
			if (GetNextToken()[0] == "seperator" && GetToken()[1] == ";") {
				fout << "<Scan> ::= get ( <IDs> ) ;" << endl;
			}
          return true;
        }
      }
    }
  }
  return false;
}
///////////////////////////////////////
bool V(){
  if(GetNextToken()[0] == "keyword" && GetToken()[1] == "while"){
    if(GetNextToken()[0] == "seperator" && GetToken()[1] == "("){
      if (W()){
        if (GetNextToken()[0] == "seperator" && GetToken()[1] == ")"){
          if(O()){
            fout << "<While> ::=  while ( <Condition> ) <Statement>" << endl;
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
        fout << "<Condition> ::= <Expression> <Relop> <Expression>"<<endl;
        return true;
      }
    }
  }
  return false;
}
///////////////////////////////////////
bool X(){
  if (GetNextToken()[0] == "operator" && (GetToken()[1] == "==" || GetToken()[1] == "/=" || GetToken()[1] == ">=" || GetToken()[1] == "<=" || GetToken()[1] == ">" || GetToken()[1] == "<")){
	  fout << "<Relop> ::= == | /= | > | < |  => | <=" << endl;
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
  int counter = GetTokenCounter();

  if (GetNextToken()[0] == "operator" && GetToken()[1] == "+"){
    if(Z()){
      if(YPrime()){
		fout << "<Expression> ::= <Expression> + <Term>" << endl;
        return true;
      }
    }
  }

  SetTokenCounter(counter);

  if (GetNextToken()[0] == "operator" && GetToken()[1] == "-"){
    if(Z()){
      if(YPrime()){
		fout << "<Expression> ::= <Expression> - <Term>" << endl;
        return true;
      }
    }
  }

  fout << "<Expression> ::= <Term>" << endl;
  SetTokenCounter(counter);
  return true;
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
	int counter = GetTokenCounter();

  if(GetNextToken()[0] == "operator" && GetToken()[1] == "*"){
    if(AA()){
      if(ZPrime()){
		fout << "<Term> ::= <Term>  *  <Factor>" << endl;
        return true;
      }
    }
  }

  SetTokenCounter(counter);

  if(GetNextToken()[0] == "operator" && GetToken()[1] == "/"){
    if(AA()){
      if(ZPrime()){
		fout << "<Term> ::= <Term>  /  <Factor>" << endl;
        return true;
      }
    }
  }

  fout << "<Term> ::= <Factor>" << endl;
  SetTokenCounter(counter);
  return true;
}
///////////////////////////////////////
bool AA(){
  int counter = GetTokenCounter();

  if(GetNextToken()[0] == "operator" && GetToken()[1] == "-"){
    if(BB()){
		fout << "<Factor> ::= - <Primary>" << endl;
      return true;
    }
  }

  SetTokenCounter(counter);

  if (BB()){
	  fout << "<Factor> ::= <Primary>" << endl;
    return true;
  }
  return false;
}
///////////////////////////////////////
bool BB(){
  int counter = GetTokenCounter();

  if (GetNextToken()[0] == "identifier") {
	  if (GetNextToken()[0] == "seperator" && GetToken()[1] == "(") {
		  if (M()) {
			  if (GetNextToken()[0] == "seperator" && GetToken()[1] == ")") {
				  fout << "<Primary> ::= <Identifier> ( <IDs> )" << endl;
				  return true;
			  }
		  }
	  }
  }

  SetTokenCounter(counter);

  if(GetNextToken()[0] == "identifier"){
	  fout << "<Primary> ::= <Identifier>" << endl;
    return true;
  }

  SetTokenCounter(counter);

  if(GetNextToken()[0] == "integer"){
	  fout << "<Primary> ::= <Integer>" << endl;
    return true;
  }

  SetTokenCounter(counter);

  if(GetNextToken()[0] == "seperator" && GetToken()[1] == "("){
    if (Y()){
      if (GetNextToken()[0] == "seperator" && GetToken()[1] == ")"){
		  fout << "<Primary> ::= ( <Expression> )" << endl;
        return true;
      }
    }
  }

  SetTokenCounter(counter);

  if(GetNextToken()[0] == "real"){
	  fout << "<Primary> ::= <Real>" << endl;
    return true;
  }

  SetTokenCounter(counter);

  if(GetNextToken()[0] == "keyword" && (GetToken()[1] == "true" || GetToken()[1] == "false")){
	  fout << "<Primary> ::= " << GetToken()[1] << endl;
    return true;
  }
  return false;
}
///////////////////////////////////////
int main(){
	Lexer();
  if(APrime()){
    fout << "Parsing complete.";
  }
}
