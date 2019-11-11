#include "lexer.h"
#include <vector>
using namespace std;
ifstream src("./output.txt");

//Beginning of rules
bool APrime(){//the rule that augments the grammar. Just calls A. Not sure if it needs to check anything.
  if (A()){
    return true;
  }
  return false;
}
bool A(){
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
  return false;
}
bool B(){
  if(C()){
    return true;
  }
  else{
    CC();
  }
  return false;
}
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
bool E(){
  if(F()){
    return true;
  }
  else{
    CC();
  }
  return false;
}
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
bool G(){
  if (M()){
    if (H()){
      return true;
    }
  }
  return false;
}
bool H(){
  if (Lexer() == "integer"){
    return true;
  }
  else if (Lexer() == "keyword" && (keyword == "true" || keyword == "false")){
    return true;
  }
  return false;
}
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
bool J(){
  if(K()){
    return true;
  }
  else {
    CC();
  }
  return false;
}
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
bool L(){
  if(H()){
    if(M()){
      return true;
    }
  }
  return false;
}
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
bool N(){
  if(O()){
    return true;
  }
  else if(O()){
    if(N()){
      return true;
    }
  }
  return false;
}
bool O(){
  if(P(){

  }
  else if(Q()){
    return true;
  }
  else if(R()){
    return true;
  }
  else if(S()){
    return true;
  }
  else if(T()){
    return true;
  }
  else if(U()){
    return true;
  }
  else if(V()){
    return true;
  }
  return false;
}
bool P(){
  if(Lexer() == "seperator" && ch == '{'){
    if (N()){
      if(Lexer() == "seperator" && ch == '}'){
        return true;
      }
    }
  }
  return false;
}
bool Q(){
  if (Lexer() == "identifier"){
    if(Lexer() == "seperator" && ch == '='){
      if(Y()){
        if(Lexer() == "seperator" && ch == ';'){
          return true;
        }
      }
    }
  }
  return false;
}
bool R(){
  if(Lexer() == "keyword" && keyword == "if"){
    if(Lexer() == "seperator" && ch == '('{
      if(W()){
        if(Lexer() == "seperator" && ch == ')'){
          if(O()){
            if(Lexer() == "keyword" && keyword == "fi"){
              return true;
            }
          }
        }
      }
    }
    return false;
  }
  else if(Lexer() == "keyword" && keyword == "if"){
    if(Lexer() == "seperator" && ch == '('{
      if(W()){
        if(Lexer() == "seperator" && ch == ')'){
          if(O()){
            if(Lexer() == "keyword" && keyword == "otherwise"){
              if(O()){
                if(Lexer() == "keyword" && keyword == "fi"){
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
bool S(){
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
  return false;
}
bool T(){
  if(Lexer() == "keyword" && keyword == "put"){
    if(Lexer() == "seperator" && ch == '('){
      if (Y()){
        if (Lexer() == "seperator" && ch == ')'){
          return true;
        }
      }
    }
  }
  return false;
}
bool U(){
  if(Lexer() == "keyword" && keyword == "get"){
    if(Lexer() == "seperator" && ch == '('){
      if (M()){
        if (Lexer() == "seperator" && ch == ')'){
          return true;
        }
      }
    }
  }
  return false;
}
bool V(){
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
  return false;
}
bool W(){
  if(Y()){
    if(X()){
      if(Y()){
        return true;
      }
    }
  }
  return false;
}
bool X(){
  if (Lexer() == "operator" && (ch + next == "==" || ch + next == "/=" || ch + next == "<=" || ch + next == "=>" || ch == '<' || ch == '>')){
    return true;
  }
  return false;
}
bool Y(){
  if(Z()){
    if(YPrime()){
      return true;
    }
  }
  return false;
}
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
bool Z(){
  if(AA()){
    if(ZPrime()){
      return true;
    }
  }
  return false;
}
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
  else if(Lexer() == "keyword" && keyword == "true" || keyword == "false"){
    return true;
  }
  return false;
}

void CC(){
  LexerDone();
}
int main(){
  if(APrime()){
    cout << "Parsing complete.";
  }
}
