// minunatul nostru main
// mashallah

#include <iostream>
#include <string>
#include "command.h"
#include "utils.h"


using namespace std;

int main() {
  string input;
  int tokenCount;
  getline(cin, input);
  Command command(input);
 	command.print();

  getline(cin, input);
  ParenthesisTokenizer parenthesis(input);
  string* tokenizedParenthesis = new string[parenthesis.getNoValuesInParenthesis()];
  tokenizedParenthesis = parenthesis.getTokenizedParenthesis(); 
  for(int i = 0; i < parenthesis.getNoValuesInParenthesis(); i++) {
    cout << endl << tokenizedParenthesis[i];
  }

  return 0;
};