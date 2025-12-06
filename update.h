#ifndef UPDATE_H
#define UPDATE_H

#include <iostream>
#include <string>

using namespace std;

class Update{
private:
    string tableName = "";
    string updatedColumn = "";
    string newValue = "";
    string checkedColumn = "";
    string checkedValue = "";
public:
    const static int TABLE_NAME_POSITION;
    const static int UPDATED_COLUMN_POSITION;
    const static int NEW_VALUE_POSITION;
    const static int CHECKED_COLUMN_POSITION;
    const static int CHECKED_VALUE_POSITION; 

    Update(string* commandTokens, int noTokens) {
        setTableName(commandTokens[TABLE_NAME_POSITION]);
        setUpdatedColumn(commandTokens[UPDATED_COLUMN_POSITION]);
        setNewValue(commandTokens[NEW_VALUE_POSITION]);
        setCheckedColumn(commandTokens[CHECKED_COLUMN_POSITION]);
        setCheckedValue(commandTokens[CHECKED_VALUE_POSITION]);
    }

    void setTableName(string value) {
        this->tableName = value;
    }

    void setUpdatedColumn(string value) {
        this->updatedColumn = value;
    }

    void setNewValue(string value) {
        this->newValue = value;
    }

    void setCheckedColumn(string value) {
        this->checkedColumn = value;
    }

    void setCheckedValue(string value) {
        this->checkedValue = value;
    } 

    void print() {
        cout << endl << "Table name: " << this->tableName;
        cout << endl << "Updated Column: " << this->updatedColumn;
        cout << endl << "New Value: " << this->newValue;
        cout << endl << "Checked Column: " << this->checkedColumn;
        cout << endl << "Checked Value: " << this->checkedValue;
    }
};

const int Update::TABLE_NAME_POSITION = 1;
const int Update::UPDATED_COLUMN_POSITION = 3;
const int Update::NEW_VALUE_POSITION = 4;
const int Update::CHECKED_COLUMN_POSITION = 6;
const int Update::CHECKED_VALUE_POSITION = 7; 
#endif