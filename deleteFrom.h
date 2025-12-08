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
  const static int COLUMN_VALUE_POZITION;
  DeleteFrom(string *commandTokens, int noTokens) {
    setTableName(commandTokens[DeleteFrom::TABLE_NAME_POZITION]);
    setColumnName(commandTokens[DeleteFrom::COLUMN_NAME_POZITION]);
    setColumnValue(commandTokens[DeleteFrom::COLUMN_VALUE_POZITION]);
  }

  DeleteFrom(DeleteFrom& other) {
    if(this == &other) return;
    this->tableName = other.tableName;
    this->columnName = other.columnName;
    this->columnValue = other.columnValue;
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

  bool operator==(DeleteFrom& other) {
    if(this->tableName != other.tableName) return false;
    if(this->columnName != other.columnName) return false;
    if(this->columnValue != other.columnValue) return false;
    return true;
  }

  friend void operator<<(ostream& console, DeleteFrom& deleteFrom);
};

void operator<<(ostream& console, DeleteFrom& deleteFrom) {
    console << endl << "Table: " << deleteFrom.tableName;
    console << endl << "Column: " << deleteFrom.columnName;
    console << endl << "Value to be Deleted: " << deleteFrom.columnValue;
  }

const int DeleteFrom::TABLE_NAME_POZITION = 2;
const int DeleteFrom::COLUMN_NAME_POZITION = 4;
const int DeleteFrom::COLUMN_VALUE_POZITION = 5;

#endif