#include "lexer.h"
#include <vector>
using namespace std;
ifstream src("./output.txt");
//class that holds lexeme and token for each line
//and has member functions to get them
/*
class input{
public:
  string token;
  string lexeme;
  string gettoken(){
    return this->token;
  }
  string getlexeme(){
    return this->lexeme;
  }
};
string token;
string lexeme;
string curLine;
//vector that holds all of the input lines defined above
vector<input> inputs;
//function that puts the output of the lexer into an easy to traverse vector.
void getInputs(){
  string token;
  string lexeme;
  input temp;
  while (!src.eof()){
    src >> token;
    src >> lexeme;
    temp.token = token;
    temp.lexeme = lexeme;
    inputs.push_back(temp);
  }
  temp.token = "$";
  temp.lexeme = "$";
  inputs.push_back(temp);
  for (input i : inputs){
    cout << i.token << " ----- " << i.lexeme << endl;
  }
}
*/
//Beginning of rules
void APrime(){//the rule that augments the grammar. Just calls A. Not sure if it needs to check anything.
  if (A()){
    return true;
  }
}
void A(){

}
void B(){

}
void C(){

}
void D(){

}
void E(){

}
void F(){

}
void G(){

}
void H(){

}
void I(){

}
void J(){

}
void K(){

}
void L(){

}
void M(){

}
void N(){

}
void O(){

}
void P(){

}
void Q(){

}
void R(){

}
void S(){

}
void T(){

}
void U(){

}
void V(){
  if(Lexer() == "keyword" && keyword == "while"){
    if(Lexer() == "seperator" && ch == '('){
      if (W()){
        if (Lexer() == "seperator" && ch == ')'){
          if(O()){
            return true;
          }
        }
      }
    }
  }
}
void W(){
  if(Y()){
    if(X()){
      if(Y()){
        return true;
      }
    }
  }
}
void X(){
  string operatorrrrrr = ch + next;
  if (Lexer() == "operator" && (operatorrrrrr == "==" || operatorrrrrr == "/=" || operatorrrrrr == "<=" || operatorrrrrr == "=>" || ch == '<' || ch == '>')){
    return true;
  }
}
void Y(){
  if(Z()){
    if(YPrime()){
      return true;
    }
  }
}
void YPrime(){
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
}
void Z(){
  if(AA()){
    if(ZPrime()){
      return true;
    }
  }
}
void ZPrime(){
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
}
void AA(){
  if(Lexer() == "operator" && ch == '-'){
    if(BB()){
      return true;
    }
  }
  else if (BB()){
    return true;
  }
}
void BB(){
  if(Lexer() == "identifier" || Lexer() == "integer" || (Lexer() == "seperator" && ch == '(')){
    if(Lexer() == "seperator" && ch == '('){
      if (M()){
        if (Lexer() == "seperator" && ch == ')'){
          return true;
        }
      }
    }
    else if (Y()){
      if (Lexer() == "seperator" && ch == ')'){
        return true;
      }
    }
    return true;
  }
  else if(Lexer() == "real"){
    return true;
  }
  else if(Lexer() == "keyword" && (keyword == "true" || keyword == "false")){
    return true;
  }
}
void CC(){
  LexerDone();
}
int main(){
}
