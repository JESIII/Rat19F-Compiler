#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <vector>
#include <cstring>
using namespace std;
class input{
public:
  string token;
  string lexeme;
	size_t lineNumber;
	input(string tok, string lex, size_t line){
		token = tok;
		lexeme = lex;
		lineNumber = line;
	}
  string gettoken(){
    return this->token;
  }
  string getlexeme(){
    return this->lexeme;
  }
};
ofstream fout("output.txt");
ifstream fin("C:/Users/tinco/Dropbox (CSU Fullerton)/323/Rat19F-Compiler/Lexer/Test-Cases/sample.rat19");
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
				tokens.push_back(vector<string>{ "keyword", keyword, lineNumber });
			}
			else {
				tokens.push_back(vector<string>{ "identifier", identifier, lineNumber });
			}
		}

		else if (isdigit(ch)) {
			number = getNumOrReal(ch);
			if (number.find(".") != -1) {
				tokens.push_back(vector<string>{ "real", number, lineNumber });
			}
			else {
				tokens.push_back(vector<string>{ "integer", number, lineNumber });
			}
		}

		else if (in_array(ch, seperators, 10)) {
			ch2 = fin.peek();
			if (ch2 == '%') {
				fin.get();
				tokens.push_back(vector<string>{ "seperator", string() + ch + ch2, lineNumber });
			}
			else if (ch2 == ']') { //handles *]
				fin.get();
				tokens.push_back(vector<string>{ "seperator", string() + ch + ch2, lineNumber });
			}
			else if (ch2 == '*') { //handles [*
				char seeker = fin.get();
				while(seeker != '*'){
					fin.get(seeker);
				}
				fin.unget();
				tokens.push_back(vector<string>{ "seperator", string() + ch + ch2, lineNumber });
			}
			else if (ch == '*'){ //Since * can be an operator or beginning of sep, we need this to handle it being an op.
				tokens.push_back(vector<string>{ "operator", string() + ch, lineNumber });
			}
			else {
				tokens.push_back(vector<string>{ "seperator", string() +  ch, lineNumber });
			}
		}

		else if (in_array(ch, operators, 8)) {
			ch2 = fin.peek();
			if (ch2 == '>') {
				fin.get();
				tokens.push_back(vector<string>{ "operator", string() + ch + ch2, lineNumber });
			}
			else if (ch2 == '=') {
				fin.get();
				tokens.push_back(vector<string>{ "operator", string() + ch + ch2, lineNumber });
			}
			else {
				tokens.push_back(vector<string>{ "operator", string() + ch, lineNumber });
			}
		}
	}
	//fout.close();
  //fin.close();
	fout << "LEXER COMPLETE!" << endl;
  for (unsigned int i = 0; i < tokens.size(); i++) {
	  fout << tokens.at(i)[0] << ": " << tokens.at(i)[1] << endl;
  }
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
			  fout << "B %% J N %%" << endl;
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
	  fout << "C" << endl;
    return true;
  }

  fout << "Empty" << endl;
  SetTokenCounter(counter);
  return true;
}
///////////////////////////////////////
bool C(){
  if(D()){
	  int counter = GetTokenCounter();
	  if (C()) {
		  fout << "D C" << endl;
		  return true;
	  }
	  else {
		  fout << "D" << endl;
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
				  fout << "function <Identifier> ( E ) J I" << endl;
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
	fout << "F" << endl;
    return true;
  }

  fout << "Empty" << endl;
  SetTokenCounter(counter);
  return true;
}
///////////////////////////////////////
bool F(){
  if(G()){
	  int counter = GetTokenCounter();
	  if (GetNextToken()[0] == "seperator" && GetToken()[1] == ",") {
		  if (F()) {
			  fout << "G , F" << endl;
			  return true;
		  }
	  }
	  else {
		  fout << "G" << endl;
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
	  fout << "M H" << endl;
      return true;
    }
  }
  return false;
}
///////////////////////////////////////
bool H(){
  if (GetNextToken()[0] == "keyword" && (GetToken()[1] == "int" || GetToken()[1] == "boolean" || GetToken()[1] == "real")){
	fout << GetToken()[1] << endl;
    return true;
  }
  return false;
}
///////////////////////////////////////
bool I(){
  if(GetNextToken()[0] == "seperator" && GetToken()[1] == "{"){
    if(N()){
      if(GetNextToken()[0] == "seperator" && GetToken()[1] == "}"){
		fout << "{ N }" << endl;
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
	fout << "K" << endl;
    return true;
  }

  fout << "Empty" << endl;
  SetTokenCounter(counter);
  return true;
}
///////////////////////////////////////
bool K(){
  if(L()){
    if(GetNextToken()[0] == "seperator" && GetToken()[1] == ";"){
		int counter = GetTokenCounter();
		if (K()) {
			fout << "L ; K" << endl;
			return true;
		}
		else {
			fout << "L ;" << endl;
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
	  fout << "H M" << endl;
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
		  fout << "<Identifier> , M" << endl;
		  return true;
	  }
	  else {
		  fout << "<Identifier>" << endl;
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
		  fout << "<Statement> <Statement List>" << endl;
		  return true;
	  }
	  else {
		  SetTokenCounter(counter);
		  fout << "<Statement>" << endl;
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
    fout << "<Compound> "<<endl;
    return true;
  }

  SetTokenCounter(counter);

  if(Q()){
    fout << "<Assign>   "<<endl;
    return true;
  }

  SetTokenCounter(counter);

  if(R()){
    fout << "<If>   "<<endl;
    return true;
  }

  SetTokenCounter(counter);

  if(S()){
    fout << "<Return>      "<<endl;
    return true;
  }

  SetTokenCounter(counter);

  if(T()){
    fout << "<Print>       "<<endl;
    return true;
  }

  SetTokenCounter(counter);

  if(U()){
    fout << "<Scan>     "<<endl;
    return true;
  }

  SetTokenCounter(counter);

  if(V()){
    fout << "<While> "<<endl;
    return true;
  }

  return false;
}
///////////////////////////////////////
bool P(){
  if(GetNextToken()[0] == "seperator" && GetToken()[1] == "{"){
    if (N()){
      if(GetNextToken()[0] == "seperator" && GetToken()[1] == "}"){
        fout << "{  <Statement List>  } "<<endl;
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
          fout << "<Identifier> = <Expression> ;"<<endl;
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
              fout << "if  ( <Condition>  ) <Statement>   fi" << endl;
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
                  fout << "if  ( <Condition>  ) <Statement>   otherwise  <Statement>  fi " << endl;
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
				fout << "return <Expression> ;" << endl;
				return true;
			}
		}

		SetTokenCounter(counter);

		if (GetNextToken()[0] == "seperator" && GetToken()[1] == ";") {
			fout << "return <Expression> ;" << endl;
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
				fout << "put ( <Expression>);" << endl;
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
				fout << "get ( <IDs> );" << endl;
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
        fout << "<Condition> ::=     <Expression>  <Relop>   <Expression>"<<endl;
        return true;
      }
    }
  }
  return false;
}
///////////////////////////////////////
bool X(){
  if (GetNextToken()[0] == "operator" && (GetToken()[1] == "==" || GetToken()[1] == "/=" || GetToken()[1] == ">=" || GetToken()[1] == "<=" || GetToken()[1] == ">" || GetToken()[1] == "<")){
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
        return true;
      }
    }
  }

  SetTokenCounter(counter);

  if (GetNextToken()[0] == "operator" && GetToken()[1] == "-"){
    if(Z()){
      if(YPrime()){
        return true;
      }
    }
  }

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
        return true;
      }
    }
  }

  SetTokenCounter(counter);

  if(GetNextToken()[0] == "operator" && GetToken()[1] == "/"){
    if(AA()){
      if(ZPrime()){
        return true;
      }
    }
  }

  SetTokenCounter(counter);
  return true;
}
///////////////////////////////////////
bool AA(){
  int counter = GetTokenCounter();

  if(GetNextToken()[0] == "operator" && GetToken()[1] == "-"){
    if(BB()){
      return true;
    }
  }

  SetTokenCounter(counter);

  if (BB()){
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
				  return true;
			  }
		  }
	  }
  }

  SetTokenCounter(counter);

  if(GetNextToken()[0] == "identifier"){
    return true;
  }

  SetTokenCounter(counter);

  if(GetNextToken()[0] == "integer"){
    return true;
  }

  SetTokenCounter(counter);

  if(GetNextToken()[0] == "seperator" && GetToken()[1] == "("){
    if (Y()){
      if (GetNextToken()[0] == "seperator" && GetToken()[1] == ")"){
        return true;
      }
    }
  }

  SetTokenCounter(counter);

  if(GetNextToken()[0] == "real"){
    return true;
  }

  SetTokenCounter(counter);

  if(GetNextToken()[0] == "keyword" && (GetToken()[1] == "true" || GetToken()[1] == "false")){
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
