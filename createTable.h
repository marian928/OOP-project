#ifndef CREATETABLE_H
#define CREATETABLE_H
#pragma once

#include <iostream>
#include <string>
#include "Command.h"
#include "Utils.h"

using namespace std;

enum DataType {
    TYPE_INT,
    TYPE_STRING,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_BOOL,
    TYPE_DATE,
    TYPE_CHAR,
    TYPE_TEXT,
    TYPE_UNKNOWN
};

class CreateTable
{
private:
    string tableName;
    string* columnNames;
    DataType* columnTypes;      
    int* columnSizes;
    string* defaultValues;
    int noColumns;

 
    DataType parseDataType(const string& typeStr) {
        string upperType = "";
        for (size_t i = 0; i < typeStr.length(); i++) {
            upperType += toupper(typeStr[i]);
        }

        if (upperType == "INT" || upperType == "INTEGER") {
            return TYPE_INT;
        }
        else if (upperType == "VARCHAR" || upperType == "STRING") {
            return TYPE_STRING;
        }
        else if (upperType == "FLOAT") {
            return TYPE_FLOAT;
        }
        else if (upperType == "DOUBLE" || upperType == "REAL" || upperType == "DECIMAL") {
            return TYPE_DOUBLE;
        }
        else if (upperType == "BOOL" || upperType == "BOOLEAN") {
            return TYPE_BOOL;
        }
        else if (upperType == "DATE" || upperType == "DATETIME" || upperType == "TIMESTAMP") {
            return TYPE_DATE;
        }
        else if (upperType == "CHAR" || upperType == "CHARACTER") {
            return TYPE_CHAR;
        }
        else if (upperType == "TEXT") {
            return TYPE_TEXT;
        }

        return TYPE_UNKNOWN;
    }

  
    static string dataTypeToString(DataType type)
    {
        switch (type) {
        case TYPE_INT: return "INT";
        case TYPE_STRING: return "STRING";
        case TYPE_FLOAT: return "FLOAT";
        case TYPE_DOUBLE: return "DOUBLE";
        case TYPE_BOOL: return "BOOL";
        case TYPE_DATE: return "DATE";
        case TYPE_CHAR: return "CHAR";
        case TYPE_TEXT: return "TEXT";
        case TYPE_UNKNOWN: return "UNKNOWN";
        default: return "UNKNOWN";
        }
    }

public:

    CreateTable() : tableName(""), columnNames(nullptr), columnTypes(nullptr),
        columnSizes(nullptr), defaultValues(nullptr), noColumns(0)
    {}


    CreateTable(Command& cmd) : tableName(""), columnNames(nullptr), columnTypes(nullptr),
        columnSizes(nullptr), defaultValues(nullptr), noColumns(0)
    {
        string* tokens = cmd.getTokenizedInput();
        int noTokens = cmd.getNoTokens();
        if (noTokens < 4)
        {
            cout << "Error: Incomplete CREATE TABLE command!" << endl;
            delete[] tokens;
            return;
        }

        tableName = tokens[2];

        ParenthesisTokenizer pTokenizer(tokens[3]);
        string* columnTokens = pTokenizer.getTokenizedParenthesis();
        int noTokensInParenthesis = pTokenizer.getNoValuesInParenthesis();

        int i = 0;
        int colCount = 0;
        while (i < noTokensInParenthesis)
        {
            i++;
            if (i >= noTokensInParenthesis)
                break;
            i++;
            if (i >= noTokensInParenthesis)
                break;
            colCount++;
            if (i < noTokensInParenthesis)
            {
                string upperToken = columnTokens[i];
                for (size_t j = 0; j < upperToken.length(); j++)
                {
                    upperToken[j] = toupper(upperToken[j]);
                }

                if (upperToken == "DEFAULT")
                {
                    i++;
                    i++;
                }
            }
        }

        noColumns = colCount;

        if (noColumns == 0)
        {
            delete[] columnTokens;
            delete[] tokens;
            return;
        }

        columnNames = new string[noColumns];
        columnTypes = new DataType[noColumns];
        columnSizes = new int[noColumns];
        defaultValues = new string[noColumns];

        for (int j = 0; j < noColumns; j++)
        {
            columnNames[j] = "";
            columnTypes[j] = TYPE_UNKNOWN;
            columnSizes[j] = -1;
            defaultValues[j] = "";
        }

        i = 0;
        int colIndex = 0;

        while (i < noTokensInParenthesis && colIndex < noColumns)
        {
            columnNames[colIndex] = columnTokens[i];
            i++;

            if (i >= noTokensInParenthesis)
                break;

            string typeToken = columnTokens[i];
            i++;

            int openParen = typeToken.find('(');
            if (openParen != string::npos)
            {
                int closeParen = typeToken.find(')');
                if (closeParen != string::npos)
                {
                    string typeStr = typeToken.substr(0, openParen);
                    columnTypes[colIndex] = parseDataType(typeStr);

                    string sizeStr = typeToken.substr(openParen + 1, closeParen - openParen - 1);
                    try
                    {
                        columnSizes[colIndex] = stoi(sizeStr);
                    }
                    catch (...)
                    {
                        columnSizes[colIndex] = -1;
                    }
                }
                else
                {
                    columnTypes[colIndex] = parseDataType(typeToken);
                }
            }
            else
            {
                columnTypes[colIndex] = parseDataType(typeToken);
            }

            if (i < noTokensInParenthesis)
            {
                string upperToken = columnTokens[i];
                for (size_t j = 0; j < upperToken.length(); j++)
                {
                    upperToken[j] = toupper(upperToken[j]);
                }

                if (upperToken == "DEFAULT")
                {
                    i++;
                    if (i < noTokensInParenthesis)
                    {
                        defaultValues[colIndex] = columnTokens[i];
                        i++;
                    }
                }
            }

            colIndex++;
        }

        delete[] columnTokens;
        delete[] tokens;
    }

    ~CreateTable()
    {
        delete[] columnNames;
        delete[] columnTypes;
        delete[] columnSizes;
        delete[] defaultValues;
    }

    friend ostream& operator<<(ostream& os, const CreateTable& ct)
    {
        os << "♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥" << endl;
        os << "♥             CREATE TABLE PARSED                          ♥" << endl;
        os << "♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥" << endl;
        os << endl;

        os << "Table name: " << ct.tableName << endl;
        os << "Number of columns: " << ct.noColumns << endl;
        os << endl;

        if (ct.noColumns > 0)
        {
            os << "♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥" << endl;
            os << "♥             COLUMN DEFINITIONS                          ♥" << endl;
            os << "♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥" << endl;

            for (int i = 0; i < ct.noColumns; i++)
            {
                os << "│ Column " << (i + 1) << ":";
                os << endl;

                os << "│   Name:    " << ct.columnNames[i] << endl;
                os << "│   Type:    ";

                switch (ct.columnTypes[i]) {
                case TYPE_INT: os << "INT"; break;
                case TYPE_STRING: os << "STRING"; break;
                case TYPE_FLOAT: os << "FLOAT"; break;
                case TYPE_DOUBLE: os << "DOUBLE"; break;
                case TYPE_BOOL: os << "BOOL"; break;
                case TYPE_DATE: os << "DATE"; break;
                case TYPE_CHAR: os << "CHAR"; break;
                case TYPE_TEXT: os << "TEXT"; break;
                case TYPE_UNKNOWN: os << "UNKNOWN"; break;
                default: os << "UNKNOWN"; break;
                }

                if (ct.columnSizes[i] != -1)
                {
                    os << "(" << ct.columnSizes[i] << ")";
                }
                os << endl;

                if (!ct.defaultValues[i].empty())
                {
                    os << "│   Default: " << ct.defaultValues[i] << endl;
                }

                if (i < ct.noColumns - 1)
                {
                    os << "│" << endl;
                }
            }

            os << "♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥" << endl;
        }
        else {
            os << "No columns defined!" << endl;
        }

        return os;
    }

    string getTableName()
    {
        return tableName;
    }

    int getNoColumns()
    {
        return noColumns;
    }

    string* getColumnNames()
    {
        if (noColumns == 0)
            return nullptr;
        string* copy = new string[noColumns];
        for (int i = 0; i < noColumns; i++)
        {
            copy[i] = columnNames[i];
        }
        return copy;
    }

    DataType* getColumnTypes()
    {
        if (noColumns == 0)
            return nullptr;
        DataType* copy = new DataType[noColumns];
        for (int i = 0; i < noColumns; i++)
        {
            copy[i] = columnTypes[i];
        }
        return copy;
    }

    int* getColumnSizes()
    {
        if (noColumns == 0)
            return nullptr;
        int* copy = new int[noColumns];
        for (int i = 0; i < noColumns; i++)
        {
            copy[i] = columnSizes[i];
        }
        return copy;
    }

    string* getDefaultValues()
    {
        if (noColumns == 0)
            return nullptr;
        string* copy = new string[noColumns];
        for (int i = 0; i < noColumns; i++)
        {
            copy[i] = defaultValues[i];
        }
        return copy;
    }

    string getColumnName(int index)
    {
        if (index >= 0 && index < noColumns)
            return columnNames[index];
        return "";
    }

    DataType getColumnType(int index)
    {
        if (index >= 0 && index < noColumns)
            return columnTypes[index];
        return TYPE_UNKNOWN;
    }

    string getColumnTypeAsString(int index)
    {
        if (index >= 0 && index < noColumns)
            return dataTypeToString(columnTypes[index]);
        return "UNKNOWN";
    }

    int getColumnSize(int index)
    {
        if (index >= 0 && index < noColumns)
            return columnSizes[index];
        return -1;
    }

    string getDefaultValue(int index)
    {
        if (index >= 0 && index < noColumns)
            return defaultValues[index];
        return "";
    }

    bool isValid()
    {
        return !tableName.empty() && noColumns > 0;
    }

    void printDetailed()
    {
        cout << "INFO" << endl;
        cout << "Table name: '" << tableName << "'" << endl;
        cout << "Number of columns: " << noColumns << endl;

        for (int i = 0; i < noColumns; i++) {
            cout << "\nColumn " << i << ":" << endl;
            cout << "  Name: '" << columnNames[i] << "'" << endl;
            cout << "  Type: '" << dataTypeToString(columnTypes[i]) << "'" << endl;
            cout << "  Type Enum Value: " << columnTypes[i] << endl;
            cout << "  Size: " << columnSizes[i] << endl;
            cout << "  Default: '" << defaultValues[i] << "'" << endl;
        }
    }
};

#endif
