#ifndef SQLDATABASE_H
#define SQLDATABASE_H

#include <filesystem>
#include <string>
#include <unordered_map>
#include <sqlite3.h>
#include <iostream>


using namespace std;

// Data Stucture proveniente del Paso 1. (Tokenization of documents)
typedef unordered_map<string, vector<int>> Words_t;
string arrayToString(vector<int>& array);
void accessDataBase(sqlite3* db);
void createTable(sqlite3* db);
void saveData(sqlite3* db);
void prepareSaveStatement(sqlite3* db, sqlite3_stmt* statement, string guardadoStatement);


Words_t paso1(filesystem::path PATH);

#endif SQLDATABASE_H