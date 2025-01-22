//LEMBRAR DE ADICIONAR UM THROW AO USAR AS FUNCOES CREATE, DELETE E UPDATE

#include <iostream>

#include "Deck.h"

void Deck::create(std::string title, std::string subject, int levelCollection_id){
    sqlite3* db;
    int exit = sqlite3_open("dados.db", &db);

    //teste para saber se abriu o sql
    if (exit) {
        //throw std::runtime_error(std::string("Erro ao abrir banco de dados: ") + sqlite3_errmsg(db));
        return;
    }

    //linha de comando para executar o SQL
    std::string sql = "INSERT INTO Deck (title, subject, levelCollection_id) VALUES ('" +
                      title + "', '" + subject + "', " + std::to_string(levelCollection_id) + ");";
    
    char* errMsg;
    //executa comando
    exit = sqlite3_exec(db,sql.c_str(),0,0,&errMsg);

    //teste para erros do sql
    if(exit != SQLITE_OK){
        std::string errorMessage = "Erro ao inserir dados: " + std::string(errMsg);
        sqlite3_free(errMsg);
        //throw std::runtime_error(errorMessage);
        return;
    }

    //fechar o arquivo sql
    sqlite3_close(db);
}

void Deck::delet(int id){
    sqlite3* db;
    int exit = sqlite3_open("dados.db", &db);

    //teste para saber se abriu o sql
    if (exit) {
        //throw std::runtime_error(std::string("Erro ao abrir banco de dados: ") + sqlite3_errmsg(db));
        return;
    }
    
    std::string sql = "DELETE FROM Deck WHERE id = " + std::to_string(id) + ";";

    char* errMsg;
    exit = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);

    if (exit != SQLITE_OK) {
        std::string errorMessage = "Erro ao deletar dados: " + std::string(errMsg);
        sqlite3_free(errMsg);
        //throw std::runtime_error(errorMessage);
        return;
    }

    //fechar o arquivo sql
    sqlite3_close(db);
}

void Deck::update(std::string title, std::string subject, int levelCollection_id, int id){
    sqlite3* db;
    int exit = sqlite3_open("dados.db", &db);

    //teste para saber se abriu o sql
    if (exit) {
        //throw std::runtime_error(std::string("Erro ao abrir banco de dados: ") + sqlite3_errmsg(db));
        return;
    }


    std::string sql = "UPDATE Deck SET title = '"
     + title + "', subject = '" + subject + "' WHERE id = " + std::to_string(id) + ";";
    char* errMsg;
    exit = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);

    if (exit != SQLITE_OK) {
        std::string errorMessage = "Erro ao atualizar dados: " + std::string(errMsg);
        sqlite3_free(errMsg);
        //throw std::runtime_error(errorMessage);
        return;
    }

    //fechar o arquivo sql
    sqlite3_close(db);
}