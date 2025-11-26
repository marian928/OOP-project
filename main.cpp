// minunatul nostru main
// mashallah

#include <iostream>
#include <string>
#include "command.h"

using namespace std;

int main() {
  string input;
  int tokenCount;
  getline(cin, input);
  Command command(input);
 	command.print();
  return 0;
};