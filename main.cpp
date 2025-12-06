// minunatul nostru main
// mashallah

#include <iostream>
#include <string>
#include "command.h"
#include "utils.h"
#include "insertInto.h"
#include "deleteFrom.h"
#include "select.h"
#include "update.h"

using namespace std;

int main() {
  string input;
  int tokenCount;
  getline(cin, input);
  // Command command(input);
 	// command.print();

  // getline(cin, input);
  // ParenthesisTokenizer parenthesis(input);
  // string* tokenizedParenthesis = new string[parenthesis.getNoValuesInParenthesis()];
  // tokenizedParenthesis = parenthesis.getTokenizedParenthesis(); 
  // for(int i = 0; i < parenthesis.getNoValuesInParenthesis(); i++) {
  //   cout << endl << tokenizedParenthesis[i];
  // }

  // Command command(input);
  // InsertIntoCommand insert(command.getTokenizedInput(), 5);
  // insert.printOutput();

  Command command(input);
  command.print();
  // DeleteFrom deleteColumn(command.getTokenizedInput(), command.getNoTokens());
  // // deleteColumn.print();
  // Select select(command.getTokenizedInput(), command.getNoTokens());
  // select.print();
  Update update(command.getTokenizedInput(), command.getNoTokens());
  update.print();
  return 0;
};