#ifndef INSERT_INTO_COMMAND_H
#define INSERT_INTO_COMMAND_H

#include <iostream>
#include <string>
#include "command.h"
#include "utils.h"

using namespace std;

class InsertIntoCommand {
private:
    string tableName = "";
    string* columnNames = nullptr;   // optional, not used yet
    string* values = nullptr;
    int noValues = 0;
    int noColumns = 0;

public:
    const static int TABLE_NAME_POSITION;
    const static int VALUES_POSITION;

    InsertIntoCommand(string* commandTokens, int noTokens) {
        delete[] this->columnNames;
        delete[] this->values;
        if(commandTokens == nullptr) {
            tableName = "";
            columnNames = nullptr;
            values = nullptr;
            noValues = 0;
            noColumns = 0;
        }
            tableName = commandTokens[InsertIntoCommand::TABLE_NAME_POSITION];
            columnNames = nullptr;
            ParenthesisTokenizer parenthesis(commandTokens[InsertIntoCommand::VALUES_POSITION]);
            noValues = parenthesis.getNoValuesInParenthesis();
            noColumns = noValues;//temporary
            if(noValues > noColumns) throw "To Many Values";
            else if(noValues < noColumns) throw "Not enought Values";
            values = new string[noValues];
            for(int i = 0; i < noValues; i++)
                values[i] = parenthesis.getTokenizedParenthesis()[i];
        
    }

    
    
    InsertIntoCommand(const InsertIntoCommand& other) {
        tableName = other.tableName;
        noValues = other.noValues;
        noColumns = other.noColumns;
        
        if (other.values != nullptr) {
            values = new string[noValues];
            for (int i = 0; i < noValues; i++)
            values[i] = other.values[i];
        }
        else {
            values = nullptr;
        }
        
        if (other.columnNames != nullptr) {
            columnNames = new string[noColumns];
            for (int i = 0; i < noColumns; i++)
            columnNames[i] = other.columnNames[i];
        }
        else {
            columnNames = nullptr;
        }
    }
    
    InsertIntoCommand& operator=(const InsertIntoCommand& other) {
        if (this != &other) {
            delete[] values;
            delete[] columnNames;
            
            tableName = other.tableName;
            noValues = other.noValues;
            noColumns = other.noColumns;
            
            if (other.values != nullptr) {
                values = new string[noValues];
                for (int i = 0; i < noValues; i++)
                values[i] = other.values[i];
            }
            else {
                values = nullptr;
            }
            
            if (other.columnNames != nullptr) {
                columnNames = new string[noColumns];
                for (int i = 0; i < noColumns; i++)
                columnNames[i] = other.columnNames[i];
            }
            else {
                columnNames = nullptr;
            }
        }
        return *this;
    }
    
    
    void setValues(string* newValues, int noNewValues) {
        if (newValues == nullptr) {
            cout << "\nInvalid INSERT command!";
            return;
        }
        delete[] this->values;
        
        values = new string[noValues];
        
        for (int i = 0; i < noValues; i++) {
            values[i] = newValues[i];
        }
        this->noValues = noNewValues;
    }
    
    void printOutput() {
        cout << endl << "Table: " << this->tableName;
        cout << endl << "Columns: " << this->noValues;
        for (int i = 0; i < this->noValues; i++)
        cout << endl << "Column " << i+1 << ": " << this->values[i];
    }

    ~InsertIntoCommand() {
        delete[] columnNames;
        delete[] values;
    }
};

const int InsertIntoCommand::TABLE_NAME_POSITION = 2;
const int InsertIntoCommand::VALUES_POSITION = 4;

#endif 
