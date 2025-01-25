#include "deckdao.h"

DeckDAO::DeckDAO(DatabaseConnection& database) : db(database) {} 
DeckDAO::~DeckDAO(){}

bool DeckDAO::deckExists(int id){
    bool exists = false;
    std::string sql = "SELECT COUNT(*) FROM Deck WHERE id = ?;";
    sqlite3_stmt* stmt;

    db.beginTransaction();

    if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            exists = sqlite3_column_int(stmt, 0) > 0;
        }
    } else {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
    }

    db.commitTransaction();

    sqlite3_finalize(stmt);
    return exists;
}
int DeckDAO::countDecks(){
    int count = 0;
    std::string sql = "SELECT COUNT(*) FROM Deck;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            count = sqlite3_column_int(stmt, 0);
        }
    } else {
        sqlite3_finalize(stmt);
        throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
    }


    sqlite3_finalize(stmt);
    return count;
}




int DeckDAO::getDeckID(Deck& deck){
    int deck_id = -1;  // Valor padrão para indicar erro caso não encontre

    std::string sql = "SELECT id FROM Deck WHERE title = ? AND subject = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, deck.getTitle().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, deck.getSubject().c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            deck_id = sqlite3_column_int(stmt, 0);
        } else {
            throw std::runtime_error("Erro ao preparar consulta: NAO FOI POSSIVEL ENCONTRAR CARD COM ESSE NOME E ASSUNTO");
        }
    } else {
        throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
    }

    sqlite3_finalize(stmt);
    return deck_id;
}
Deck DeckDAO::getDeckById(int id){
    Deck deck("nulo","nulo");  // Objeto vazio para retorno padrão caso não encontre nada
    deck.setId(-1);

    std::string sql = "SELECT id, title, subject FROM Deck WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);  // Associa o valor do ID na query preparada

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            deck.setId(sqlite3_column_int(stmt, 0));
            deck.setTitle(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            deck.setSubject(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        } else {
            throw std::runtime_error("Erro ao preparar consulta: Nao foi possivel achar deck com este ID");
        }
    } else {
        throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
    }

    sqlite3_finalize(stmt);
    return deck;
}



bool DeckDAO::createDeck(Deck& deck){
    std::string sql = "INSERT INTO Deck (title, subject) VALUES (?, ?);";
    sqlite3_stmt* stmt;

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
        }

        // Vincula os valores
        sqlite3_bind_text(stmt, 1, deck.getTitle().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, deck.getSubject().c_str(), -1, SQLITE_STATIC);

        // Executa a consulta
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw std::runtime_error("Erro ao executar consulta: " + db.getLastError());
        }

        // Obtém o ID do Deck recém-criado
        int newId = sqlite3_last_insert_rowid(db.getDB());
        deck.setId(newId);  // Atualiza o objeto Deck com o novo ID
        std::cout << "Deck criado com ID: " << newId << std::endl;

        sqlite3_finalize(stmt);
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Erro ao criar Deck: " << e.what() << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }
    
}
bool DeckDAO::deleteDeck(int id){
    if(deckExists(id)){
        //executa comando sql
        if(db.executeQuery("DELETE FROM Deck WHERE id = " + std::to_string(id) + ";")){
            return true;
        }
        return false; //SE OCORRER ERRO IRA LANCAR UM THROW std::runtime_error()
    }
    return false;
}
bool DeckDAO::updateDeck(const Deck& deck){
    if(deckExists(deck.getId())){
        if(db.executeQuery("UPDATE Deck SET title = '"
        + deck.getTitle() + "', subject = '" + deck.getSubject() + "' WHERE id = " + std::to_string(deck.getId()) + ";")){
            return true;
        }
        return false; //SE OCORRER ERRO IRA LANCAR UM THROW std::runtime_error()
    }
    return false;
}


//FALTA CRIAR card.h PARA RESOLVER
/*
bool DeckDAO::addCardToDeck(int deck_id, int card_id);
bool DeckDAO::deleteCardFromDeck(int deck_id, int card_id);

//FALTA CRIAR card.h PARA RESOLV
std::array<Card,50> DeckDAO::getCardsByDeckId(int deck_id);*/

//FALTA CRIAR CONSTRUTOR PADRAO
std::array<Deck,50> DeckDAO::getAllDecks(){
    std::array<Deck, 50> decks;
    size_t index = 0;

    std::string sql = "SELECT id, title, subject FROM Deck LIMIT 50;";
    sqlite3_stmt* stmt;

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
            while (sqlite3_step(stmt) == SQLITE_ROW && index < 50) {
                int id = sqlite3_column_int(stmt, 0);
                std::string title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                std::string subject = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

                Deck deck(title, subject);
                deck.setId(id);  // Se existir um setter para ID, ou adicionar no construtor

                decks[index++] = deck;
            }
        } else {
            throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro ao buscar decks: " << e.what() << std::endl;
    }

    sqlite3_finalize(stmt);
    return decks;
}



