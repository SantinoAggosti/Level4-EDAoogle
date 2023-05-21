/**
 * @file main.cpp
 * @author Marc S. Ressl
 * @brief
 * @version 0.2
 *
 * @copyright Copyright (c) 2022-2023
 *
 */

#include <iostream>

#include <microhttpd.h>
#include <sqlite3.h>
#include "CommandLineParser.h"
#include "HttpServer.h"
#include "EDAoogleHttpRequestHandler.h"

using namespace std;


int main(int argc, const char *argv[])
{

    /**********    CREACION DE BASE DE DATOS    **********/
    char* errMsg = nullptr;

    // 0. Creacion de objeto de base de datos s1lite3
    sqlite3* db;

    // 1. Acceso a base de datos
    int result = sqlite3_open("dataBase.db", &db);
    if (result != SQLITE_OK) {
        // Handle the error case
    }
    else {
        cout << "1. Acceso a base de datos exitoso" << endl;
    }

    // 2.Formar un CREATE TABLE statement "Reverse Index" .
    // Statement indica tabla de 1000 Columnas, 
    string crearTablaSQL = "CREATE TABLE IF NOT EXISTS MyTable (";

    // La primer Columan guarda cada palabra identificada a lo largo de nuestras paginas web

    crearTablaSQL += "Palabra INTEGER PRIMARY KEY,";
    for (int i = 1; i <= 1000; ++i) {
        // Por ahora el tipo de cada columna representa el path del documento
        crearTablaSQL += "Documento" + to_string(i) + " TEXT";
        if (i != 1001) {
            crearTablaSQL += ",";
        }
    }
    crearTablaSQL += ");";

    // 3. Ejectutar el Statment guardado en el string crearTableSQL
    result = sqlite3_exec(db, crearTablaSQL.c_str(), nullptr, nullptr, &errMsg);
    if (result != SQLITE_OK) {
        std::cout << "2. SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return 1;
    }
    else {
        cout << "2. Ejecucion de Statement Exitoso" << endl;
    }



    // . Cerrar el acceso a la base de datos
    sqlite3_close(db);


    CommandLineParser parser(argc, argv);

    // Configuration
    int port = 8000;
    string homePath = "www";

    // Parse command line
    if (parser.hasOption("--help"))
    {
        cout << "edahttpd 0.1" << endl
             << endl;
        cout << "Usage: edahttpd [-p PORT] [-h HOME_PATH]" << endl;

        return 0;
    }

    if (parser.hasOption("-p"))
        port = stoi(parser.getOption("-p"));

    if (parser.hasOption("-h"))
        homePath = parser.getOption("-h");

    // Start server
    HttpServer server(port);

    EDAoogleHttpRequestHandler edaOogleHttpRequestHandler(homePath);
    server.setHttpRequestHandler(&edaOogleHttpRequestHandler);

    if (server.isRunning())
    {
        cout << "Running server..." << endl;

        // Wait for keyboard entry
        char value;
        cin >> value;

        cout << "Stopping server..." << endl;
    }
}
