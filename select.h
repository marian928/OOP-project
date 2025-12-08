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

    Select(Select& other) {
        delete[] this->columnNames;
        if(other.columnNames == nullptr) columnNames = nullptr;
        else {
            this->noColumns = other.noColumns;
            columnNames = new string[this->noColumns];
            for(int i = 0; i < this->noColumns; i++) {
                this->columnNames[i] = other.columnNames[i];
            }
            this->tableName = other.tableName;
            this->columnName = other.columnName;
            this->columnValue = other.columnValue;
        }
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

    bool operator==(Select& other) {
        if(this->noColumns != other.noColumns) return false;
        for(int i = 0; i < this->noColumns; i++) {
            if(this->columnNames[i]!= other.columnNames[i]) return false;
        }
        if(this->tableName != other.tableName) return false;
        if(this->columnName != other.columnName) return false;
        if(this->columnValue != other.columnValue) return false;
        return true;
    }

    friend void operator<<(ostream& console, Select& select);

};

void operator<<(ostream& console, Select& select) {
    console << endl << "Selected Table: " << select.tableName;
    console << endl << "Selected Columns: ";
    for(int i = 0; i < select.noColumns; i++) {
        console << select.columnNames[i] << " ";
    }
    console << endl << "Column for extra selection: " << select.columnName;
    console << endl << "Value: " << select.columnValue;
}

const int Select::TABLE_NAME_POSITION = 3;
const int Select::COLUMN_NAME_POSITION = 5;
const int Select::COLUMN_VALUE_POSITION = 6;
const int Select::COLUMN_NAMES_POZITION = 1;
#endif