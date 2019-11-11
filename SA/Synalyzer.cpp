#include "lexer.h"
#include <vector>
using namespace std;
ifstream src("./output.txt");

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
  if(K()){
    return true;
  }
  else {
    CC();
  }
}
void K(){
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
}
void L(){
  if(H()){
    if(M()){
      return true;
    }
  }
}
void M(){
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
}
void N(){
  if(O()){
    return true;
  }
  else if(O()){
    if(N()){
      return true;
    }
  }
}
void O(){
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
}
void P(){
  if(Lexer() == "seperator" && ch == '{'){
    if (N()){
      if(Lexer() == "seperator" && ch == '}'){
        return true;
      }
    }
  }
}
void Q(){
  if (Lexer() == "identifier"){
    if(Lexer() == "seperator" && ch == '='){
      if(Y()){
        if(Lexer() == "seperator" && ch == ';'){
          return true;
        }
      }
    }
  }
}
void R(){
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
void BB(){ 
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
}

void CC(){
  LexerDone();
}
int main(){
  if(APrime()){
    cout << "Parsing complete.";
  }
}
