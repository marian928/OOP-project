#ifndef INDEX_H
#define INDEX_H

#include<iostream>
#include<string>
using namespace std;

class Index
{
private:
    string indexName;
    string tableName;
    string columnName;
    string command;
    bool ifDoesntExist;
public:
    Index()
    {
        this->indexName = "";
        this->tableName = "";
        this->columnName = "";
        this->command = "";
        this->command = false;
    }
    Index(string name, string table, string column)
    {
        this->indexName = name;
        this->tableName = table;
        this->columnName = column;
        this->command = "";
        this->ifDoesntExist = false;
    }

    string getIndexName()
    {
        return this->indexName;
    }
    void setIndexName(string name)
    {
        this->indexName = name;
    }
    string getTableName()
    {
        return this->tableName;
    }
    void setTableName(string table)
    {
        this->tableName = table;
    }
    string getColumnName()
    {
        return this->columnName;

    }
    void setColumnName(string column)
    {
        this->columnName = column;
    }
    string getCommand()
    {
        return this->command;
    }
    bool getIfDoesntExist()
    {
        return this->ifDoesntExist;
    }



    //Without Index:
    //SELECT * FROM users WHERE id = 100;
    //Database: "Let me check every single row one by one until I find id=100"
    //Like looking for a word in a book by reading every page
    //With Index:
    //SELECT * FROM users WHERE id = 100;  -- Same text!
    //Database: "I'll use the index on id to jump directly to row 100"
    //Like using a book index to go straight to the right page

    // set inut from tokenized command
    void setInput(string* commandTokens, int noTokens)
    {
        if (commandTokens == nullptr || noTokens < 6)
        {
            cout << "invalid CREATE INDEX command";
            return;
        }
        //CREATE INDEX index_name ON table_name(column_name)
        //[0]CREATE [1]INDEX [2]index_name [3]ON [4]table_name [5](column_name)

        // CREATE INDEX IF NOT EXISTS index_name ON table_name(column_name)  
        // Tokens: [0]CREATE [1]INDEX [2]IF [3]NOT [4]EXISTS [5]index_name [6]ON [7]table_name [8](column_name)
        int currentIndex = 2; //we start after "CREATE INDEX"
        if (noTokens >= 6 && commandTokens[2] == "IF" && commandTokens[3] == "NOT" && commandTokens[4] == "EXISTS")
        {
            this->ifDoesntExist = true;
            currentIndex = 5;//moving to index name position
        }
        //get indexname
        if (currentIndex < noTokens)
        {
            this->indexName = commandTokens[currentIndex];
            currentIndex++;
        }
        if (currentIndex < noTokens && commandTokens[currentIndex] == "ON")
        {
            currentIndex++;
        }
        else
        {
            cout << "'ON' was expected after index name";
            return;
        }
        //get tablename
        if (currentIndex < noTokens)
        {
            this->tableName = commandTokens[currentIndex];
            currentIndex++;
        }
        //column name
        if (currentIndex < noTokens)
        {
            string columnToken = commandTokens[currentIndex];
            //we have to remove parenthese if present
            if (columnToken[0] == '(' && columnToken[columnToken.length() - 1] == ')')
            {
                this->columnName = columnToken.substr(1, columnToken.length() - 2);
            }
            else
            {
                this->columnName = columnToken;
            }
        }

        //build command string for reference
        this->command = "CREATE INDEX";
        if (this->ifDoesntExist)
        {
            this->command += "IF NOT EXISTS";
        }
        this->command += this->indexName + "ON" + this->tableName + "(" + this->columnName + ")";

    }
    //execute command
    bool execute()
    {
        if (this->indexName.empty() || this->tableName.empty() || this->columnName.empty())
        {
            cout << "cant execute,missing index info";
            return false;
        }

        cout << endl << "executing: CREATE INDEX";
        if (this->ifDoesntExist)
        {
            cout << " IF NOT EXISTS";
        }
        cout << " " << this->indexName << " ON" << this->tableName << "("
            << this->columnName << ")";
        // add actual database index creation
        cout << "index created succesfully";
        return true;
    }
    void print()
    {
        cout << endl << "Index Name: " << this->indexName;
        cout << endl << "Table: " << this->tableName;
        cout << endl << "Column: " << this->columnName;
        cout << endl << "If Not Exists: " << (this->ifDoesntExist ? "Yes" : "No");
        cout << endl << "Full Command: " << this->command;
    }

    
// the actual creation in the database file isnt yet completed, it will go in the bool execute() after the files coourse








}; // end of class

#endif

