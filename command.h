#ifndef COMMAND_H
#define COMMAND_H
#pragma once

#include <iostream>
#include <string>

using namespace std;

class Command {
private:
  string input = "";
  string* tokenizedInput = nullptr;
  int noTokens = 0;
  // Internal scan function: if outArray == 0 it just counts tokens,
  // otherwise it also writes them into outArray.

public:
  
  Command() {}

  Command(const string input) : input(input) {
    tokenize();
  }

  string* getTokenizedInput() {
    string* copy = new string[this->noTokens];
    for(int i = 0; i < this->noTokens; i++) 
      copy[i] = this->tokenizedInput[i]; 
    return copy;
  }

  void tokenCounter(string value) {
   bool inParentheses = false;
    this->noTokens = 0;
    string token;
    for(int i = 0; i < this->input.size(); i++) {
      char c = input[i];
      if(inParentheses) {
        if(c == ')') {
          token += c; 
          inParentheses = false;
        } else token += c;
      } else {
        if(c == '(') {
          if(!token.empty()) {
            this->noTokens++;
            token.clear();
          }
          token += c;
          inParentheses = true;
        } else if (c == ' ' || c == ',') {
          if(!token.empty()){
            this->noTokens++;
            token.clear();
          } 
        }else token += c;
      }
      
      cout << endl << this->noTokens << " ---> " << c << endl;
    }
    if (!token.empty()) {
        ++this->noTokens;
    }
    
      cout << endl << this->noTokens << endl;
  }

  void tokenize() {
    delete[] tokenizedInput;
    tokenCounter(this->input);
    cout << endl << this->noTokens;
    if(this->noTokens == 0) {
      tokenizedInput = nullptr;
      return;
    }
    tokenizedInput = new string[this->noTokens];
    bool inParentheses = false;
    int noToken = 0;
    string token = "";
    for(int i = 0; i < this->input.size(); i++) {
      char c = input[i];
      if(inParentheses) {
        if(c == ')') {
          token += c; 
          inParentheses = false;
        } else token += c;
      } else {
        if(c == '(') {
          if(!token.empty()) {
            this->tokenizedInput[noToken] = token;
            noToken++;
            token.clear();
          }
          token += c;
          inParentheses = true;
        } else if (c == ' ' || c == ',') {
          if(!token.empty()){
            this->tokenizedInput[noToken] = token;
            noToken++;
            token.clear();
          }
        } else token += c;
      }
     

    }
     if (!token.empty()) {
        this->tokenizedInput[noToken] = token;
        ++noToken;
      }
  }

  void print() { 
    cout << endl << this->input; 
    cout << endl << this->noTokens;
    for(int i = 0 ; i < this->noTokens; i++) 
    {
      cout << endl << this->tokenizedInput[i];
    }
    
  }
  ~Command() {
    delete[] this->tokenizedInput; 
  }
};
#endif