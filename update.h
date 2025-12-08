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

    Update(Update& other) {
        if(this == &other) return;
        this->tableName = other.tableName;
        this->updatedColumn = other.updatedColumn;
        this->newValue = other.newValue;
        this->checkedColumn = other.checkedColumn;
        this->checkedValue = other.checkedValue;
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

    bool operator==(Update& update){
        if(this->tableName != update.tableName) return false;
        if(this->updatedColumn != update.updatedColumn) return false;
        if(this->newValue != update.newValue) return false;
        if(this->checkedColumn != update.checkedColumn) return false;
        if(this->checkedValue != update.checkedValue) return false;
        return true;
    }

    friend void operator<<(ostream& console, Update &u);
};

void operator<<(ostream& console, Update &u) {
    console << endl << u.tableName;
    console << endl << u.updatedColumn;
    console << endl << u.newValue;
    console << endl << u.checkedColumn;
    console << endl << u.checkedValue;
}

const int Update::TABLE_NAME_POSITION = 1;
const int Update::UPDATED_COLUMN_POSITION = 3;
const int Update::NEW_VALUE_POSITION = 4;
const int Update::CHECKED_COLUMN_POSITION = 6;
const int Update::CHECKED_VALUE_POSITION = 7; 
#endif