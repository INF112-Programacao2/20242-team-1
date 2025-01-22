#include <iostream>
#include <sqlite3.h>
#include <vector>
#include <string>
#include <array>

#include "card.h"
#include "deck.h"

class DatabaseConnection {
private:
    sqlite3* db;
    std::string db_name = "dados.db";
    std::string last_error;
public:
    DatabaseConnection();
    ~DatabaseConnection();

    bool openConnection();
    void closeConnection();

    bool executeQuery(const std::string& query);
    /*
    std::vector<std::vector<std::string>> fetchQuery(const std::string& query);
    */
    bool beginTransaction();
    bool commitTransaction();
    bool rollbackTransaction();

    std::string getLastError() const;
    sqlite3* getDB();
    void setDatabaseName(const std::string& name);

};