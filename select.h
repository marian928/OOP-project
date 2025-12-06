#ifndef SELECT_H
#define SELECT_H

#include <iostream>
#include <string>
#include "utils.h"

using namespace std;

class Select {
private:
    string* columnNames = nullptr;
    int noColumns = 0;
    string tableName = "";
    string columnName = "";
    string columnValue = "";
public:
    const static int TABLE_NAME_POSITION;
    const static int COLUMN_NAME_POSITION;
    const static int COLUMN_VALUE_POSITION;
    const static int COLUMN_NAMES_POZITION;

    
    Select(string* commandTokens, int noTokens) {
        if(commandTokens[COLUMN_NAMES_POZITION] != "ALL") {
            ParenthesisTokenizer tokenizedParenthesis(commandTokens[COLUMN_NAMES_POZITION]);
            setColumnNames(tokenizedParenthesis.getTokenizedParenthesis(), tokenizedParenthesis.getNoValuesInParenthesis());
        }
        setTableName(commandTokens[TABLE_NAME_POSITION]);
        setColumnName(commandTokens[COLUMN_NAME_POSITION]);
        setColumnValue(commandTokens[COLUMN_VALUE_POSITION]);
    }

    void setColumnNames(string* values, int noValues) {
        delete[] columnNames;
        this->columnNames = new string[noValues];
        for(int i = 0; i < noValues; i++) {
            this->columnNames[i] = values[i];
        }
        this->noColumns = noValues;
    }

    void setTableName(string value) {
        this->tableName = value;
    }
    void setColumnName(string value) {
        this->columnName = value;
    }
    void setColumnValue(string value) {
        this->columnValue = value;
    }

    ~Select() {
        delete[] columnNames;
    }

    void print() {
        cout << endl << "Selected Table: " << this->tableName;
        cout << endl << "Selected Columns: ";
        for(int i = 0; i < this->noColumns; i++) {
            cout << columnNames[i] << " ";
        }
        cout << endl << "Column for extra selection: " << columnName;
        cout << endl << "Value: " << columnValue;
    }
};

const int Select::TABLE_NAME_POSITION = 3;
const int Select::COLUMN_NAME_POSITION = 5;
const int Select::COLUMN_VALUE_POSITION = 6;
const int Select::COLUMN_NAMES_POZITION = 1;
#endif