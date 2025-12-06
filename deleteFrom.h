#ifndef DELETE_FROM_H
#define DELETE_FROM_H
// DELETE FROM nume_tabela WHERE nume_coloană = valoare (DELETE permite doar o
// coloană în clauza WHERE)

#include "command.h"
#include "utils.h"
#include <iostream>
#include <string.h>

using namespace std;

class DeleteFrom {
private:
  string tableName = "";
  string columnName = "";
    string columnValue = "";
public:
  const static int TABLE_NAME_POZITION;
  const static int COLUMN_NAME_POZITION;
  DeleteFrom(string *commandTokens, int noTokens) {
    setTableName(commandTokens[DeleteFrom::TABLE_NAME_POZITION]);
    if (checkInput(commandTokens[DeleteFrom::COLUMN_NAME_POZITION])) {
      setColumnName(commandTokens[DeleteFrom::COLUMN_NAME_POZITION]);
    } else {
        string separatedValues[2];
        string token = "";
        for (int i = 0; i < commandTokens[DeleteFrom::COLUMN_NAME_POZITION].size(); i++) {
            if (commandTokens[DeleteFrom::COLUMN_NAME_POZITION][i] == '=') {
                separatedValues[0] = token;
                token = "";
            } else {
                token += commandTokens[DeleteFrom::COLUMN_NAME_POZITION][i];
            }
        }
        separatedValues[1] = token;
        setColumnName(separatedValues[0]);
        setColumnValue(separatedValues[1]);
    }
  }
  void setTableName(string value) { this->tableName = value; }
  void setColumnName(string value) { this->columnName = value; }
  void setColumnValue(string value) {
    this->columnValue = value;
  }
  bool checkInput(string value) {
    // checks if the token with the column name has the value
    for (int i = 0; i < value.size(); i++) {
      if (value[i] == '=') {
        return false;
      }
    }
    return true;
  }

  void print() {
    cout << endl << "Table: " << this->tableName;
    cout << endl << "Column: " << this->columnName;
    cout << endl << "Value to be Deleted: " << this->columnValue;
  }
};

const int DeleteFrom::TABLE_NAME_POZITION = 2;
const int DeleteFrom::COLUMN_NAME_POZITION = 4;

#endif