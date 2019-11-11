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

//Beginning of rules
void APrime(){//the rule that augments the grammar. Just calls A. Not sure if it needs to check anything.
  if (A()){
    return true;
  }
}
void A(){
  if(B()){
    if(Lexer() == "seperator" && ch + next == "%%"){
      if(J()){
        if(N()){
          if(Lexer() == "seperator" && ch + next == "%%"){
            return true;
          }
        }
      }
    }
  }
}
void B(){
  if(C()){
    return true;
  }
  else{
    CC();
  }
}
void C(){
  if(D()){
    return true;
  }
  else if (D()){
    if(C()){
      return true;
    }
  }
}
void D(){
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
}
void E(){
  if(F()){
    return true;
  }
  else{
    CC();
  }
}
void F(){
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
}
void G(){
  if (M()){
    if (H()){
      return true;
    }
  }
}
void H(){
  if (Lexer() == "integer"){
    return true;
  }
  else if (Lexer() == "keyword" && (keyword == "true" || keyword == "false")){
    return true;
  }
}
void I(){
  if(Lexer() == "seperator" && ch == '{'){
    if(N()){
      if(Lexer() == "seperator" && ch == '}'){
        return true;
      }
    }
  }
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
  if(Lexer() == "keyword" && keyword == "return"){
    if (Lexer() == "seperator" && ch == ';'){
      return true;
    }
    else if(Y()){
      if (Lexer() == "seperator" && ch == ';'){
        return true;
      }
    }
  }
}
void T(){
  if(Lexer() == "keyword" && keyword == "put"){
    if(Lexer() == "seperator" && ch == '('){
      if (Y()){
        if (Lexer() == "seperator" && ch == ')'){
          return true;
        }
      }
    }
  }
}
void U(){
  if(Lexer() == "keyword" && keyword == "get"){
    if(Lexer() == "seperator" && ch == '('){
      if (M()){
        if (Lexer() == "seperator" && ch == ')'){
          return true;
        }
      }
    }
  }
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
  if (Lexer() == "operator" && (ch + next == "==" || ch + next == "/=" || ch + next == "<=" || ch + next == "=>" || ch == '<' || ch == '>')){
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
void BB(){ //may have to rewrite this one in proper order.
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
*/
void CC(){
  LexerDone();
}
int main(){
  while(Lexer() != "$"){

  }
}
