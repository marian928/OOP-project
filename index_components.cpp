#include "index_components.h"
#include<string>
Index::Index()
{
	indexName = "";
	tableName = "";
	columnName = "";

}
//Index myIndex;
//myIndex.getIndexName()  // Correct - myIndex object's method
//myIndex.Index()         // WRONG - can't call constructor on object
Index:Index(string name, string table, string column)
{
	indexName = name;
	tableName = table;
	columnName = column;
}

string Index::getIndexName() {
	return this->indexName;
}//getter was written in the header,and here we DEFINE it

string Index::getTableName() {
	return this->tableName;
}

string Index::getColumnName() {
	return this->columnName;
}

void Index::setIndexName(string name) {
	this->indexName = name;
}

void Index::setTableName(string table) {
	this->tableName = table;
}

void Index::setColumnName(string column) {
	this->columnName = column;
}

CreateIndexCommand::CreateIndexCommand()
{
	this->commandText = "";
	this->ifNotExists = false;
}

CreateIndexCommand::CreateIndexCommand(string command)
{
	this->commandText = command;
	this->ifNotExists = false;
	this->parse(command);
}

bool CreateIndexCommand::parse(string command)
{
	this->commandText = command;
	//does it contain "create index?"
	if (command.find("CREATE INDEX") != string::npos)
	{
		return true;
	}
	return false;
}

Index CreateIndexCommand::getIndex()
{
	return Index("test_index", "test", "testcolumn");
}


string CreateIndexCommand::getCommandText() {
	return this->commandText;
}

bool CreateIndexCommand::getIfNotExists() {
	return this->ifNotExists;
}






















