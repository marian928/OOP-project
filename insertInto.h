/*

///WORK IN PROGRESS\\\

*/


#ifndef INSERT_INTO_COMMAND_H
#define INSERT_INTO_COMMAND_H

#include <iostream>
#include <string>
using namespace std;

class InsertIntoCommand {
private:
    string tableName;
    string* columnNames;   // optional, not used yet
    string* values;
    int noValues;
    int noColumns;

public:
    InsertIntoCommand() {
        tableName = "";
        columnNames = nullptr;
        values = nullptr;
        noValues = 0;
        noColumns = 0;
    }

    ~InsertIntoCommand() {
        delete[] columnNames;
        delete[] values;
    }

    // Copy constructor (Rule of 3)
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

    // Assignment operator (Rule of 3)
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

    //----------------------------------------------------------
    //   TOKEN SETTER  — FIXED VERSION
    //----------------------------------------------------------
    void setInput(string* commandTokens, int noTokens) {
        if (commandTokens == nullptr || noTokens < 4) {
            cout << "\nInvalid INSERT command!";
            return;
        }

        // Example expected:
        // INSERT INTO tableName VALUES val1 val2 val3

        tableName = commandTokens[2];

        // Reallocate value array
        delete[] values;

        // Number of values = everything after index 3 ("VALUES")
        noValues = noTokens - 4;  // correct number
        values = new string[noValues];

        // FIXED: Correct indexing
        for (int i = 0; i < noValues; i++) {
            values[i] = commandTokens[4 + i];
        }
    }

    void printOutput() {
        cout << endl << "Table: " << this->tableName;
        cout << endl << "Columns: " << this->noValues;
        for (int i = 0; i < this->noValues; i++)
            cout << endl << "Column " << i << ":" << this->values[i];
    }
};

#endif 
