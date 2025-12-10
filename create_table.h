#ifndef CREATETABLE_H
#define CREATETABLE_H
#pragma once

#include <iostream>
#include <string>
#include "Command.h"
#include "Utils.h"

using namespace std;

class CreateTable {
private:
    string tableName;           
    string* columnNames;       
    string* columnTypes;        
    int* columnSizes;          
    string* defaultValues;      
    int noColumns;              

public:
    // my default constructor
    CreateTable() : tableName(""), columnNames(nullptr), columnTypes(nullptr), columnSizes(nullptr), defaultValues(nullptr), noColumns(0)
    {}
    
    // Constructor that receives a Command object

    CreateTable(Command& cmd) : tableName(""), columnNames(nullptr), columnTypes(nullptr), columnSizes(nullptr), defaultValues(nullptr), noColumns(0) {
       
        string* tokens = cmd.getTokenizedInput();
        int noTokens = cmd.getNoTokens();
// we need to check that we have at least: CREATE TABLE name (columns)
        if (noTokens < 4) {
            cout << "Error: Incomplete CREATE TABLE command!" << endl;
            delete[] tokens;
            return;
        }
//enough for today,i want tomorrow to do columns and allocate arrays for them
tableName = tokens[2];
       
        ParenthesisTokenizer pTokenizer(tokens[3]);
        string* columnTokens = pTokenizer.getTokenizedParenthesis();
        int noTokensInParenthesis = pTokenizer.getNoValuesInParenthesis();

        int i = 0;
        int colCount = 0;
        while (i < noTokensInParenthesis) 
            { i++;
            if (i >= noTokensInParenthesis)
                break;
            i++;
            if (i >= noTokensInParenthesis)
                break;
            
            colCount++;
            
            if (i < noTokensInParenthesis) {
                string upperToken = columnTokens[i];
                for (size_t j = 0; j < upperToken.length(); j++) {
                    upperToken[j] = toupper(upperToken[j]);
                }
                
                if (upperToken == "DEFAULT") {
                    i++; // skip DEFAULT
                    i++; // skip default value
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
        columnTypes = new string[noColumns];
        columnSizes = new int[noColumns];
        defaultValues = new string[noColumns];
        
        for (int j = 0; j < noColumns; j++) {
            columnNames[j] = "";
            columnTypes[j] = "";
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

//now enough for day2(actually 3 because yesterday i took a break for learning PSM
//NEXT DAY AND THE DAY AFTER TOMORROW I WILL CONTINUE WITH EXTRACTING THE TYPES I GUESS,OVERLOADING OPERATORS AND DESTRUCTORS
