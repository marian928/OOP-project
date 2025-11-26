#pragma once
#include <iostream>
#include <string>

using namespace std;

class Command {
private:
    string input;

    // Internal scan function: if outArray == 0 it just counts tokens,
    // otherwise it also writes them into outArray.
    

public:
    void setInput(string value) {
        this->input = value;
    }

    CommandTokenizer(const string& str) :input(str) {
    
    }

    void scan(string* outArray, int& outCount) {
        bool inParentheses = false;
        string current;

        for (int i = 0; i < input.size(); ++i) {
            char c = input[i];

            if (inParantheses) 
                if (c == ')') {
                    inQuotes = false; // end of quoted section
                }
                else {
                    current += c;
                }
            }
            else {
                if (c == '(') {
                    inQuotes = true; // start quoted section
                }
                else if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
                    if (!current.empty()) {
                        if (outArray != 0) {
                            outArray[outCount] = current;
                        }
                        ++outCount;
                        current.clear();
                    }
                }
                else {
                    current += c;
                }
            }
        }

        // Last token, if any
        if (!current.empty()) {
            if (outArray != 0) {
                outArray[outCount] = current;
            }
            ++outCount;
        }
    }

    // Returns a dynamic array of tokens; tokenCount will hold the array size.
    string* tokenize(int& tokenCount) {
        tokenCount = 0;

        // First pass: count tokens
        scan(0, tokenCount);

        // Allocate exact-size array
        std::string* result = new std::string[tokenCount];

        // Second pass: actually fill the array
        int filled = 0;
        scan(result, filled);

        return result;
    }
};