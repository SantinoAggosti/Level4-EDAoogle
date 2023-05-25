#include "sqlDataBase.h"

Words_t paso1(filesystem::path PATH) {
    cout << "Paso 1 executed" << endl;
    Words_t testingMap = {};
    testingMap["Hello"] = { 12, 45 };
    testingMap["Chau"] = { 23, 45, 12 };
    testingMap["Whatssapp"] = { 23, 459, 673, 456, 23 };
    testingMap["Esa"] = { 1, 45, 67, 8, 2, 56 };
    return testingMap;
}
string arrayToString(vector<int>& array) {
    int size = (sizeof(array) / sizeof(array[0]));

    string arrayString = "";
    for (auto position : array) {
        arrayString += to_string(position);
        arrayString += ",";

    }
    arrayString.pop_back(); // Remover la ultima coma de mas
    //cout << "Array as string: " << arrayString << std::endl;
    return arrayString;
}

void accessDataBase(sqlite3 *db) {
    // 1. Acceso a base de datos
    cout << "1. Acceso a Base de Datos: " << endl;
    int result = sqlite3_open("dataBase.db", &db);
    if (result != SQLITE_OK) {
        cout << "Fallido\n" << endl;
        cout << "Result: " << result << endl;

    }
    else {
        cout << "Exitoso\n" << endl;
    }
}

void createTable(sqlite3* db) {
    // 2.1 Formar un CREATE TABLE statement "Reverse Index" .
    string main_table = "CREATE TABLE IF NOT EXISTS MyTable (tokens TEXT, documentID TEXT, positions TEXT)";
    // La primer Columan guarda cada palabra identificada a lo largo de nuestras paginas web
    char* errMsg = nullptr;

    cout << "2. Creacion de Tabla Indx: " << endl;
    int result = sqlite3_exec(db, main_table.c_str(), nullptr, nullptr, &errMsg);
    if (result != SQLITE_OK) {
        cout << "Fallida\n" << errMsg << endl;
        cout << "Result: " << result << endl;
        sqlite3_free(errMsg);
    }
    else {
        cout << "Exitosa\n" << endl;
    }
}

void saveData(sqlite3* db) {
    // 2.2 Formar un statement para el guardado de informacion en la base datos.
    string guardadoStatement = "INSERT INTO MyTable (tokens, documentID, positions) VALUES (?, ?, ?)";
    string path = "C:/Users/santi/OneDrive/Escritorio/Level4-EDAoogle/www/wiki";
    //for (auto& entry : filesystem::directory_iterator(path)) {
        filesystem::path hello;
        Words_t documentWords = paso1(hello);
        string token;
        string documentName;
        vector<int> positions;
        string arrayString;

        for (auto& word : documentWords) {

            // Valores a guardar
            token = word.first;
            documentName = "documento!";//entry.path().stem().string();
            positions = word.second;

            // Sorting the posiciones con QuickSort
            sort(positions.begin(), positions.end());

            // Traduccion a texto
            arrayString = arrayToString(positions);

            sqlite3_stmt* statement;
            // Preparacion preventiva de SQL Statment para Guardado de Datos
            cout << "3. Preparativos de Guardado de Datos: " << endl;
            int result = sqlite3_prepare_v2(db, guardadoStatement.c_str(), -1, &statement, nullptr);
            if (result != SQLITE_OK) {
                cout << "Fallido" << endl;
                cout << "Result: " << result << endl;
                const char* errorMessage = sqlite3_errmsg(db);
                cout << errorMessage << "\n" << endl;
            }
            else {
                cout << "Exitoso\n" << endl;
            }
            // Introduccion de parametros
            sqlite3_bind_text(statement, 1, token.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(statement, 2, documentName.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(statement, 3, arrayString.c_str(), -1, SQLITE_STATIC);

            // Ejecusion de SQL Statement
            cout << "4. Guardado de Datos en Base de Datos: " << endl;
            result = sqlite3_step(statement);
            if (result != SQLITE_DONE) {
                const char* errorMessage = sqlite3_errmsg(db);
                cout << "Fallido" << endl;
                cout << "Result: " << result << endl;
                cout << errorMessage << "\n" << endl;

            }
            else {
                cout << "Exitoso\n" << endl;
            }
            // Finalizacion de Statement preparado
            sqlite3_finalize(statement);

        }
    //}
}
