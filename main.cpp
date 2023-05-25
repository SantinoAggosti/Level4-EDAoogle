/**
 * @file main.cpp
 * @author Marc S. Ressl
 * @brief
 * @version 0.2
 *
 * @copyright Copyright (c) 2022-2023
 *
 */

#include <microhttpd.h>
#include "CommandLineParser.h"
#include "HttpServer.h"
#include "EDAoogleHttpRequestHandler.h"
#include "sqlDataBase.h"

#define N_DOCUMENTS 1284
// Hacer una funcion que cuente la cantidad de documentos que hay en la carpeta.




int main(int argc, const char *argv[])
{


    /**********    CREACION DE BASE DE DATOS    **********/

    // 0. Creacion de objeto de base de datos s1lite3
    sqlite3* db;
    int result;

    // 1. Acceso a base de datos
    cout << "1. Acceso a Base de Datos: " << endl;
    result = sqlite3_open("dataBase.db", &db);
    if (result != SQLITE_OK) {
        cout << "Fallido\n" << endl;
        cout << "Result: " << result << endl;

    }
    else {
        cout << "Exitoso\n" << endl;
    }
    //accessDataBase(db);
    createTable(db);
    saveData(db);


    // 3. Ejectutar el Statment guardado en el string crearTableSQL


    // 4. Iterar a lo largo de los documentos, aplicarles la funcion PASO1, iterar por
    // la estructura de datos recibida, y guardar los datos en SQL db.
    // 
    // Final. Cerrar el acceso a la base de datos
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

