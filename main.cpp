//minunatul nostru main
//mashallah

#include<iostream>
#include<string>
#include "command.h"

using namespace std;

int main()
{
	Command command;
	string input;
	getline(cin, input);
	command.setInput(input);

	return 0;
};