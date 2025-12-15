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

        //comment