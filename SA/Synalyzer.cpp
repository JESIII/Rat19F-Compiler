#include "lexer.h"
#include <vector>
using namespace std;
ifstream src("./output.txt");
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
vector<input> inputs;
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
  for (input i : inputs){
    cout << i.token << " ----- " << i.lexeme << endl;
  }
}
void APrime(){

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

}
void W(){

}
void X(){

}
void Y(){

}
void YPrime(){

}
void Z(){

}
void ZPrime(){

}
void AA(){

}
void BB(){

}
void CC(){

}
int main(){
  lex();
  getInputs();
  src.close();
}
