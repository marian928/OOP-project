#ifndef UTILS_H
#define UTILS_H
#pragma once

#include <iostream>
#include <string>

using namespace std;

class ParenthesisTokenizer {
private:
  string *tokenizedParenthesis = nullptr;
  int noValuesInParenthesis = 0;

public:
  ParenthesisTokenizer(string value) { setProcessedParanthesis(value); }
  void tokenCounter(string value) {
    this->noValuesInParenthesis = 0;
    string token;
    bool inDoubleParanthesis = false;
    for (int i = 1; i < value.size(); i++) {
      char c = value[i];
      if(c == '(') 
        inDoubleParanthesis = true;
      if ((c == ' ' || c == ',' ||  c == ')') && inDoubleParanthesis == false ) {
        if (!token.empty()) {
          this->noValuesInParenthesis++;
          token.clear();
        }
      } else{
        token += c;
        if(c == ')' ) 
          inDoubleParanthesis  = false;
      }
    }
    if (!token.empty()) {
      ++this->noValuesInParenthesis;
    }
  }

  void setProcessedParanthesis(string value) {
    delete[] this->tokenizedParenthesis;
    tokenCounter(value);
    if (this->noValuesInParenthesis == 0) {
      this->tokenizedParenthesis = nullptr;
      return;
    }
    this->tokenizedParenthesis = new string[this->noValuesInParenthesis];
    bool inParentheses = false;
    int noToken = 0;
    string token = "";
    bool inDoubleParanthesis = false;
    for (int i = 1; i < value.size(); i++) {
      char c = value[i];
      if(c == '(') 
        inDoubleParanthesis = true;
      if ((c == ' ' || c == ',' ||  c == ')') && inDoubleParanthesis == false) {
        if (!token.empty()) {
          this->tokenizedParenthesis[noToken] = token;
          noToken++;
          token.clear();
        }
      } else {
        token += c;
        if(c == ')' ) 
          inDoubleParanthesis  = false;
      }
    }

    if (!token.empty()) {
      this->tokenizedParenthesis[noToken] = token;
      ++noToken;
    }
  }

  string *getTokenizedParenthesis() {
    string *copy = new string[this->noValuesInParenthesis];
    for (int i = 0; i < this->noValuesInParenthesis; i++)
      copy[i] = this->tokenizedParenthesis[i];
    return copy;
  }
  int getNoValuesInParenthesis() { return this->noValuesInParenthesis; }
  ~ParenthesisTokenizer() { delete[] this->tokenizedParenthesis; }
};
#endif