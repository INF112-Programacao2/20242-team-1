#include "DatabaseConnection.h"

    DatabaseConnection::DatabaseConnection(){
        openConnection();
    }
    DatabaseConnection::DatabaseConnection(std::string _db_name){
        db_name=_db_name;
        openConnection();
    }
    DatabaseConnection::~DatabaseConnection(){
        closeConnection();
    }

    bool DatabaseConnection::openConnection(){
        if(sqlite3_open(db_name.c_str(),&db) == SQLITE_OK ){
            return true;
        }else{
            last_error = sqlite3_errmsg(db);
            throw std::runtime_error("Erro ao abrir banco de dados: " + std::string(last_error));
            return false;
        }
    }
    void DatabaseConnection::closeConnection(){
            if (db) {
            sqlite3_close(db);
            db = nullptr;
        }
    }

    std::string DatabaseConnection::getLastError() const{
        return last_error;
    }
    sqlite3* DatabaseConnection::getDB(){
        return db;
    }

    bool DatabaseConnection::executeQuery(const std::string& query) {
        char* errorMessage;
        if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
            last_error = errorMessage;
            std::string error_msg = "Erro ao executar query: " + last_error;
            sqlite3_free(errorMessage);  // Libera a mensagem de erro alocada pelo SQLite

            throw std::runtime_error(error_msg);
        }
        return true;
    }
    /*
    std::vector<std::vector<std::string>> DatabaseConnection::fetchQuery(const std::string& query);
    */

    bool DatabaseConnection::beginTransaction() {
    return executeQuery("BEGIN TRANSACTION;");
    }
    bool DatabaseConnection::commitTransaction() {
        return executeQuery("COMMIT;");
    }
    bool DatabaseConnection::rollbackTransaction() {
        return executeQuery("ROLLBACK;");
    }
