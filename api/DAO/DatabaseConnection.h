#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <iostream>
#include <vector>
#include <string>
#include <array>

#include "..\card.h"
#include "..\deck.h"
#include "sqlite3.h"

class DatabaseConnection {
private:
    sqlite3* db;
    std::string db_name = "dados.db";
    std::string last_error;
public:
    DatabaseConnection();       //ABRE O ARQUIVO dados.db
    ~DatabaseConnection();      //FECHA O ARQUIVo dados.db

    bool openConnection();      //ABRE O ARQUIVO dados.db, mas agora uma funcao
    void closeConnection();     //FECHA O ARQUIVo dados.db, mas agora uma funcao

    bool executeQuery(const std::string& query); //EXECUTA COMANDO SQL
    /*
    std::vector<std::vector<std::string>> fetchQuery(const std::string& query);
    */
    bool beginTransaction();
    bool commitTransaction();
    bool rollbackTransaction();

    std::string getLastError() const;                       //RETORNA ULTIMO ERRO OCORRIDO
    sqlite3* getDB();                                       //PEGA O ARQUIVO .db
    void setDatabaseName(const std::string& name);          //MUDA NOME DA DATABASE(talvez retirar)

};

#endif