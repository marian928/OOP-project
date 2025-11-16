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
public:
	Index()
	{
		this->indexName = "";
		this->tableName = "";
		this->columnName = "";
	}
	Index(string name, string table, string column)
	{
		this->indexName = name;
		this->tableName = table;
		this->columnName = column;
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
};

//Without Index:
//SELECT * FROM users WHERE id = 100;
//Database: "Let me check every single row one by one until I find id=100"
//Like looking for a word in a book by reading every page
//With Index:
//SELECT * FROM users WHERE id = 100;  -- Same text!
//Database: "I'll use the index on id to jump directly to row 100"
//Like using a book index to go straight to the right page

class CreateIndexCommand
{
private:
	string command;
	bool ifDoesntExist;
	Index parsedIndex; //store our parsed index
public:
	CreateIndexCommand()
	{
		this->command = "";
		this->ifDoesntExist = false;
		this->parsedIndex = Index();
	}
	CreateIndexCommand(string command)
	{
		this->command = command;
		this->ifDoesntExist = false;
		//ifNotExists stores WHAT the user wants to happen if the index already exists.
		//CREATE INDEX idx_users ON users(id)
		//→ ifNotExists = false
		//"Create this index, and if it already exists, SHOW ME AN ERROR
		this->parsedIndex = Index();
		this->parse(command); //i send to the method,like i'd send to any getter
	}
	bool parse(string command)
	{
		this->command = command;
		if (command.find("CREATE INDEX") != string::npos) //if different than nonexistent == if "CREATE INDEX" exists within my input
		{
			this->parsedIndex = Index("realname", "realtable", "realcolumn");
			return true;
		}
		return false;
	}

	Index getIndex() //getter method returns an index object
	{
		return this->parsedIndex;
	}
	string getCommand()
	{
		return this->command;
	}
	bool getIfDoesntExist()
	{
		return this->ifDoesntExist;
	}
};


#endif
