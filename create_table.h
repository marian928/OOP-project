#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

enum DataType {
    INT_TYPE,
    STRING_TYPE,
    DOUBLE_TYPE,
    BOOL_TYPE,
    DATE_TYPE,
    CHAR_TYPE
};

struct Constraint {
    bool isPrimaryKey;
    bool isUnique;
    bool isNotNull;
    bool hasDefault;
    string defaultValue;
    int maxLength;
    bool isForeignKey;
    string foreignTable;
    string foreignColumn;

    Constraint() {
        isPrimaryKey = false;
        isUnique = false;
        isNotNull = false;
        hasDefault = false;
        defaultValue = "";
        maxLength = -1;
        isForeignKey = false;
        foreignTable = "";
        foreignColumn = "";
    }
};


struct ColumnDefinition {
    string name;
    DataType type;
    Constraint constraint;
};


class CreateTableParser {
private:
    string sql;
    size_t pos;


    void skipWhitespace() {
        while (pos < sql.length() && isspace(sql[pos])) {
            pos++;
        }
    }


    string toUpper(string str) {
        transform(str.begin(), str.end(), str.begin(), ::toupper);
        return str;
    }

  
    string readToken() {
        skipWhitespace();
        string token = "";
        
     
        if (pos < sql.length() && (sql[pos] == '\'' || sql[pos] == '"')) {
            char quote = sql[pos];
            pos++;
            while (pos < sql.length() && sql[pos] != quote) {
                token += sql[pos];
                pos++;
            }
            if (pos < sql.length()) pos++; // Skip closing quote
            return token;
        }

       
        while (pos < sql.length() && !isspace(sql[pos]) && 
               sql[pos] != '(' && sql[pos] != ')' && 
               sql[pos] != ',' && sql[pos] != ';') {
            token += sql[pos];
            pos++;
        }
        return token;
    }

  
    char peekChar() {
        skipWhitespace();
        if (pos < sql.length()) {
            return sql[pos];
        }
        return '\0';
    }

  
    char readChar() {
        skipWhitespace();
        if (pos < sql.length()) {
            return sql[pos++];
        }
        return '\0';
    }

  
    DataType parseDataType(string typeStr, int& maxLength) {
        string upperType = toUpper(typeStr);
        
        if (upperType == "INT" || upperType == "INTEGER") {
            return INT_TYPE;
        }
        else if (upperType == "VARCHAR" || upperType == "TEXT" || upperType == "STRING") {
            return STRING_TYPE;
        }
        else if (upperType == "CHAR" || upperType == "CHARACTER") {
            return CHAR_TYPE;
        }
        else if (upperType == "DOUBLE" || upperType == "FLOAT" || upperType == "REAL" || upperType == "DECIMAL") {
            return DOUBLE_TYPE;
        }
        else if (upperType == "BOOL" || upperType == "BOOLEAN") {
            return BOOL_TYPE;
        }
        else if (upperType == "DATE" || upperType == "DATETIME" || upperType == "TIMESTAMP") {
            return DATE_TYPE;
        }
        
        return INT_TYPE; // Default
    }

  
    ColumnDefinition parseColumnDefinition() {
        ColumnDefinition colDef;
        
    
        colDef.name = readToken();
        
       
        string dataTypeStr = readToken();
        int maxLength = -1;
        
        if (peekChar() == '(') {
            readChar(); // consume '('
            string lengthStr = readToken();
            maxLength = stoi(lengthStr);
            if (peekChar() == ')') {
                readChar(); // consume ')'
            }
        }
        
        colDef.type = parseDataType(dataTypeStr, maxLength);
        if (maxLength > 0) {
            colDef.constraint.maxLength = maxLength;
        }
        
       
        while (pos < sql.length()) {
            skipWhitespace();
            char nextChar = peekChar();
            
           
            if (nextChar == ',' || nextChar == ')') {
                break;
            }
            
            string constraint = readToken();
            string upperConstraint = toUpper(constraint);
            
            if (upperConstraint == "PRIMARY") {
                string key = readToken();
                if (toUpper(key) == "KEY") {
                    colDef.constraint.isPrimaryKey = true;
                    colDef.constraint.isNotNull = true;
                }
            }
            else if (upperConstraint == "UNIQUE") {
                colDef.constraint.isUnique = true;
            }
            else if (upperConstraint == "NOT") {
                string null = readToken();
                if (toUpper(null) == "NULL") {
                    colDef.constraint.isNotNull = true;
                }
            }
            else if (upperConstraint == "DEFAULT") {
                colDef.constraint.hasDefault = true;
                colDef.constraint.defaultValue = readToken();
            }
            else if (upperConstraint == "REFERENCES") {
                colDef.constraint.isForeignKey = true;
                colDef.constraint.foreignTable = readToken();
                if (peekChar() == '(') {
                    readChar(); // consume '('
                    colDef.constraint.foreignColumn = readToken();
                    if (peekChar() == ')') {
                        readChar(); // consume ')'
                    }
                }
            }
        }
        
        return colDef;
    }

public:
    CreateTableParser(string sqlStatement) {
        sql = sqlStatement;
        pos = 0;
    }

   
    bool parse(string& tableName, vector<ColumnDefinition>& columns, string& errorMessage) {
        try {
            // Read CREATE keyword
            string create = readToken();
            if (toUpper(create) != "CREATE") {
                errorMessage = "Expected 'CREATE' keyword";
                return false;
            }

          
            string table = readToken();
            if (toUpper(table) != "TABLE") {
                errorMessage = "Expected 'TABLE' keyword";
                return false;
            }

           
            tableName = readToken();
            if (tableName.empty()) {
                errorMessage = "Table name cannot be empty";
                return false;
            }

           
            if (readChar() != '(') {
                errorMessage = "Expected '(' after table name";
                return false;
            }

           
            while (true) {
                skipWhitespace();
                if (peekChar() == ')') {
                    readChar(); // consume ')'
                    break;
                }

                ColumnDefinition colDef = parseColumnDefinition();
                columns.push_back(colDef);

                skipWhitespace();
                char nextChar = peekChar();
                if (nextChar == ',') {
                    readChar(); // consume ','
                }
                else if (nextChar == ')') {
                    readChar(); // consume ')'
                    break;
                }
            }

            if (columns.empty()) {
                errorMessage = "Table must have at least one column";
                return false;
            }

            return true;
        }
        catch (exception& e) {
            errorMessage = string("Parse error: ") + e.what();
            return false;
        }
    }
};


Constraint createConstraint(bool primaryKey = false, bool unique = false, bool notNull = false,
    bool hasDefault = false, string defaultVal = "", int maxLen = -1,
    bool foreignKey = false, string refTable = "", string refColumn = "") {
    Constraint c;
    c.isPrimaryKey = primaryKey;
    c.isUnique = unique;
    c.isNotNull = notNull;
    c.hasDefault = hasDefault;
    c.defaultValue = defaultVal;
    c.maxLength = maxLen;
    c.isForeignKey = foreignKey;
    c.foreignTable = refTable;
    c.foreignColumn = refColumn;
    return c;
}


bool executeCreateTable(DatabaseEngine& db, string sql) {
    CreateTableParser parser(sql);
    string tableName;
    vector<ColumnDefinition> columns;
    string errorMessage;

    // Parse the SQL statement
    if (!parser.parse(tableName, columns, errorMessage)) {
        cout << "SQL Parse Error: " << errorMessage << endl;
        return false;
    }

  
    if (!db.createTable(tableName)) {
        return false;
    }

  
    for (size_t i = 0; i < columns.size(); i++) {
        ColumnDefinition& col = columns[i];
        
        if (!db.addColumnToTable(tableName, col.name, col.type, col.constraint)) {
            cout << "Failed to add column '" << col.name << "' to table '" << tableName << "'" << endl;
            return false;
        }
    }

    cout << "Table '" << tableName << "' created successfully with " << columns.size() << " columns!" << endl;
    return true;
}


int main() {
    DatabaseEngine db;

    cout << "\n===== CREATE TABLE SQL PARSER - DEMONSTRATION =====" << endl << endl;


    cout << "Example 1: Simple table creation" << endl;
    string sql1 = "CREATE TABLE students (student_id INT PRIMARY KEY, name VARCHAR(100) NOT NULL, age INT)";
    executeCreateTable(db, sql1);
    cout << endl;


    cout << "Example 2: Table with multiple constraints" << endl;
    string sql2 = "CREATE TABLE customers (customer_id INT PRIMARY KEY, email VARCHAR(100) UNIQUE NOT NULL, balance DOUBLE DEFAULT 0.0, is_active BOOL DEFAULT true)";
    executeCreateTable(db, sql2);
    cout << endl;

   
    cout << "Example 3: Table with foreign key" << endl;
    string sql3 = "CREATE TABLE transactions (transaction_id INT PRIMARY KEY, customer_id INT NOT NULL REFERENCES customers(customer_id), amount DOUBLE NOT NULL, date DATE NOT NULL)";
    executeCreateTable(db, sql3);
    cout << endl;


    cout << "Example 4: Complex employee table" << endl;
    string sql4 = "CREATE TABLE employees (emp_id INT PRIMARY KEY, first_name VARCHAR(50) NOT NULL, last_name VARCHAR(50) NOT NULL, email VARCHAR(100) UNIQUE NOT NULL, salary DOUBLE NOT NULL, department VARCHAR(100) DEFAULT 'General', hire_date DATE NOT NULL)";
    executeCreateTable(db, sql4);
    cout << endl;

  
    db.showTables();

    cout << "===== TABLE STRUCTURES =====" << endl << endl;
    db.describeTable("students");
    db.describeTable("customers");
    db.describeTable("transactions");
    db.describeTable("employees");

    // Test error handling
    cout << "===== ERROR HANDLING TESTS =====" << endl;
    
    cout << "Test 1: Invalid SQL syntax" << endl;
    string badSql1 = "CREATE TABEL bad_table (id INT)";
    executeCreateTable(db, badSql1);
    cout << endl;

    cout << "Test 2: Duplicate table" << endl;
    string badSql2 = "CREATE TABLE students (id INT)";
    executeCreateTable(db, badSql2);
    cout << endl;

    cout << "===== CREATE TABLE PARSER COMPLETE =====" << endl;

    return 0;
}
