#include "carddao.h"

CardDAO::CardDAO(DatabaseConnection& database) : db(database) {} 

void CardDAO::SortDate(std::vector<Card>& cards) {
    std::sort(cards.begin(), cards.end(), [](const Card& a, const Card& b) {
        return a.getLastReview().getDateBystring() < b.getLastReview().getDateBystring();
    });
}

bool CardDAO::cardExists(int id) {
    bool exists = false;
    std::string sql = "SELECT COUNT(*) FROM cards WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
        }

        sqlite3_bind_int(stmt, 1, id);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            exists = sqlite3_column_int(stmt, 0) > 0;
        } else {
            throw std::runtime_error("Erro ao executar consulta: " + db.getLastError());
        }
    } catch (const std::exception& e) {
        if (stmt) {
        sqlite3_finalize(stmt);
        }
        throw std::runtime_error("Erro em cardExists: " + std::string(e.what()));
    }
    if (stmt) {
        sqlite3_finalize(stmt);
    }

    return exists;
}

int CardDAO::countCards(int deck_id) {
    Date date;
    int count = 0;
    std::string sql = "SELECT COUNT(*) FROM cards WHERE lastReview < ? AND deck_id = ?;";
    sqlite3_stmt* stmt = nullptr;

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
        }
        sqlite3_bind_text(stmt, 1, date.getDateBystring().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, deck_id);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            count = sqlite3_column_int(stmt, 0);
        } else {
            throw std::runtime_error("Erro ao executar consulta: " + db.getLastError());
        }
    } catch (const std::exception& e) {
        if (stmt) {
        sqlite3_finalize(stmt);
        }
        throw std::runtime_error("Erro em countCards: " + std::string(e.what()));
    }
    if (stmt) {
        sqlite3_finalize(stmt);
    }

    return count;
}

int CardDAO::countCardsByDeck(int deck_id) {
    int count = 0;
    std::string sql = "SELECT COUNT(*) FROM cards WHERE deck_id = ?;";
    sqlite3_stmt* stmt = nullptr;

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
        }

        sqlite3_bind_int(stmt, 1, deck_id);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            count = sqlite3_column_int(stmt, 0);
        } else {
            throw std::runtime_error("Erro ao executar consulta: " + db.getLastError());
        }
    } catch (const std::exception& e) {
        if (stmt) {
            sqlite3_finalize(stmt);  // Liberação do recurso no caso de erro
        }
        throw std::runtime_error("Exceção capturada em countCardsByDeck: " + std::string(e.what()));
    }
    if (stmt) {
        sqlite3_finalize(stmt);  // Garante a liberação de recursos sempre
    }
    return count;
}


int CardDAO::getCardIdByCard(Card card){
    int card_id = -1;  // Valor padrão para indicar erro caso não encontre

    std::string sql = "SELECT id FROM Deck WHERE front = ? AND back = ?;";
    sqlite3_stmt* stmt;

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
        }

        sqlite3_bind_text(stmt, 1, card.getFront().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, card.getBack().c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            card_id = sqlite3_column_int(stmt, 0);
        } else {
            throw std::invalid_argument("Erro ao executar consulta: Não foi possível encontrar o card com esse nome e assunto.");
        }
    } catch (const std::exception& e) {
        if (stmt) {
        sqlite3_finalize(stmt);
        }
        throw std::runtime_error("Exceção capturada em getCardIdByCard: " + std::string(e.what()));
    }

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    return card_id;
}
Card CardDAO::getCardById(int id) {
    Card card;  // Objeto vazio para retorno padrão caso não encontre nada
    std::string sql = "SELECT id, front, back, deck_id, lastReview FROM cards WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
        }

        sqlite3_bind_int(stmt, 1, id);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            card.setId(sqlite3_column_int(stmt, 0));

            const char* frontText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            card.setFront(frontText ? frontText : "");

            const char* backText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            card.setBack(backText ? backText : "");

            card.setDeckId(sqlite3_column_int(stmt, 3));

            const char* lastReviewText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            if (lastReviewText) {
                Date a;
                a.setDateBystring(lastReviewText);
                card.setLastReview(a);
            }
        } else {
            throw std::invalid_argument("Erro ao executar consulta: Não foi possível encontrar card com este ID.");
        }
    } catch (const std::exception& e) {
        if (stmt) {
        sqlite3_finalize(stmt);
        }
        throw std::runtime_error("Exceção capturada em getCardById: " + std::string(e.what()));
    }

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    return card;
}

std::vector<Card> CardDAO::getCardsByDate(int deck_id) {
    Date date;
    std::vector<Card> cards;
    std::string sql = "SELECT id, front, back, deck_id, lastReview FROM cards WHERE lastReview < ? AND deck_id=?;";
    sqlite3_stmt* stmt = nullptr;

    try {
        // Prepara a consulta SQL
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
        }
        sqlite3_bind_text(stmt, 1, date.getDateBystring().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, deck_id);

        // Itera sobre os resultados
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            Card card;

            // Coluna 0: id
            card.setId(sqlite3_column_int(stmt, 0));

            // Coluna 1: front
            const char* frontText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            card.setFront(frontText ? frontText : "");

            // Coluna 2: back
            const char* backText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            card.setBack(backText ? backText : "");

            // Coluna 3: deck_id
            card.setDeckId(sqlite3_column_int(stmt, 3));

            // Coluna 4: lastReview
            const char* lastReviewText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            if (lastReviewText) {
                Date lastReviewDate;
                lastReviewDate.setDateBystring(lastReviewText);
                card.setLastReview(lastReviewDate);
            }

            // Adiciona o card ao vetor
            cards.push_back(card);
        }
    } catch (const std::exception& e) {
        if (stmt) {
            sqlite3_finalize(stmt);
        }
        throw std::runtime_error("Erro em getCardsByDate: " + std::string(e.what()));
    }

    // Finaliza o statement
    if (stmt) {
        sqlite3_finalize(stmt);
    }

    return cards;
}

Date CardDAO::getDateByCardId(int card_id){
    Date date;  // Objeto vazio para retorno padrão caso não encontre nada
    std::string sql = "SELECT lastReview FROM cards WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
        }

        sqlite3_bind_int(stmt, 1, card_id);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const char* lastReviewText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            if (lastReviewText) {
                date.setDateBystring(lastReviewText);
            }
        } else {
            throw std::invalid_argument("Erro ao executar consulta: Não foi possível encontrar card com este ID.");
        }
    } catch (const std::exception& e) {
        if (stmt) {
        sqlite3_finalize(stmt);
        }
        throw std::runtime_error("Exceção capturada em getDateByCardId: " + std::string(e.what()));
    }

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    return date;
}

std::vector<Card> CardDAO::getAllCards(){
    std::vector<Card> cards;
    std::string sql = "SELECT id, front, back, deck_id, lastReview FROM cards;";
    sqlite3_stmt* stmt = nullptr;

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
        }
        
        while (sqlite3_step(stmt) == SQLITE_ROW){
                Card card;

                card.setId(sqlite3_column_int(stmt, 0));

                const char* frontText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                card.setFront(frontText ? frontText : "");

                const char* backText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
                card.setBack(backText ? backText : "");

                card.setDeckId(sqlite3_column_int(stmt, 3));

                const char* lastReviewText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
                if (lastReviewText) {
                    Date a;
                    a.setDateBystring(lastReviewText);
                    card.setLastReview(a);
                }

                cards.push_back(card);
            }
    } catch (const std::exception& e) {
        if (stmt) {
        sqlite3_finalize(stmt);
        }
         throw std::runtime_error("Erro em getAllCards: " + std::string(e.what()));
    }

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    return cards;
}
std::vector<Card> CardDAO::getAllCardsSortedByDate(){
    std::vector<Card> cards;
    cards = getAllCards();
    
    SortDate(cards);

    return cards;
}
std::vector<Card> CardDAO::getCardsByDeckId(int deck_id){
    std::vector<Card> cards;
    std::string sql = "SELECT id, front, back, deck_id, lastReview FROM cards WHERE deck_id = ?;";
    sqlite3_stmt* stmt = nullptr;

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
        }

        if (sqlite3_bind_int(stmt, 1, deck_id) != SQLITE_OK) {
            throw std::runtime_error("Erro ao vincular o parâmetro deck_id.");
        }

        while (sqlite3_step(stmt) == SQLITE_ROW){
                Card card;

                card.setId(sqlite3_column_int(stmt, 0));

                const char* frontText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                card.setFront(frontText ? frontText : "");

                const char* backText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
                card.setBack(backText ? backText : "");

                card.setDeckId(sqlite3_column_int(stmt, 3));

                const char* lastReviewText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
                if (lastReviewText) {
                    Date a;
                    a.setDateBystring(lastReviewText);
                    card.setLastReview(a);
                }

                cards.push_back(card);
            }
    } catch (const std::exception& e) {
        if (stmt) {
        sqlite3_finalize(stmt);
        }
         throw std::runtime_error("Erro em getCardsByDeckId: " + std::string(e.what()));
    }

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    SortDate(cards);
    return cards;
}
std::vector<Card> CardDAO::getCardsByDeckIdSortedByDate(int deck_id){
    std::vector<Card> cards;
    cards = getCardsByDeckId(deck_id);
    
    SortDate(cards);

    return cards;
}
    

bool CardDAO::createCard(Card& card){
    std::string sql = "INSERT INTO cards (front, back, deck_id, lastReview) VALUES (?, ?,?,?);";
    sqlite3_stmt* stmt;

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consultaaa: " + db.getLastError());
        }

        // Vincula os valores
        sqlite3_bind_text(stmt, 1, card.getFront().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, card.getBack().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 3, card.getDeckId());
        sqlite3_bind_text(stmt, 4, card.getLastReview().getDateBystring().c_str(), -1, SQLITE_TRANSIENT);

        // Executa a consulta
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw std::runtime_error("Erro ao executar consulta: " + db.getLastError());
        }

        // Obtém o ID do Deck recém-criado
        int newId = sqlite3_last_insert_rowid(db.getDB());
        card.setId(newId);  // Atualiza o objeto Deck com o novo ID

        sqlite3_finalize(stmt);
        return true;
    } catch (const std::exception& e) {
        if (stmt) {
        sqlite3_finalize(stmt);
        }
         throw std::runtime_error("Erro em createCard: " + std::string(e.what()));
    }

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    return true;
}
bool CardDAO::updateCard(const Card& card) {
    std::string sql = "UPDATE cards SET front = ?, back = ?, deck_id = ?, lastReview = ? WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta de atualização: " + db.getLastError());
        }

        sqlite3_bind_text(stmt, 1, card.getFront().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, card.getBack().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 3, card.getDeckId());
        sqlite3_bind_text(stmt, 4, card.getLastReview().getDateBystring().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 5, card.getId());

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw std::runtime_error("Erro ao atualizar card: " + db.getLastError());
        }

        if (sqlite3_changes(db.getDB()) == 0) {
            throw std::runtime_error("Erro: Nenhum card foi atualizado, possivelmente o ID fornecido não existe.");
        }

        sqlite3_finalize(stmt);
        return true;
    } catch (const std::exception& e) {
        if (stmt) sqlite3_finalize(stmt);
        throw std::runtime_error("Erro em updateCard: " + std::string(e.what()));
        return false;
    }

    if (stmt) sqlite3_finalize(stmt);
    return false;
}
bool CardDAO::deleteCard(int id) {
    std::string sql = "DELETE FROM cards WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta de exclusão: " + db.getLastError());
        }

        sqlite3_bind_int(stmt, 1, id);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw std::runtime_error("Erro ao excluir card: " + db.getLastError());
        }

        if (sqlite3_changes(db.getDB()) == 0) {
            throw std::runtime_error("Erro: Nenhum card foi atualizado, possivelmente o ID fornecido não existe.");
        }

        sqlite3_finalize(stmt);
        return true;
    } catch (const std::exception& e) {
        if (stmt) sqlite3_finalize(stmt);
        throw std::runtime_error("Erro em deleteCard: " + std::string(e.what()));
        return false;
    }

    if (stmt) sqlite3_finalize(stmt);
    return false;
}
    
bool CardDAO::deleteCardsByDeckId(int deck_id) {
    std::string sql = "DELETE FROM cards WHERE deck_id = ?;";
    sqlite3_stmt* stmt = nullptr;

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta de exclusão por deck: " + db.getLastError());
        }

        sqlite3_bind_int(stmt, 1, deck_id);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw std::runtime_error("Erro ao excluir cards do deck: " + db.getLastError());
        }

        if (sqlite3_changes(db.getDB()) == 0) {
            throw std::runtime_error("Erro: Nenhum card foi atualizado, possivelmente o ID fornecido não existe.");
        }

        sqlite3_finalize(stmt);
        return true;
    } catch (const std::exception& e) {
        if (stmt) sqlite3_finalize(stmt);
        throw std::runtime_error("Erro em deleteCardsByDeckId: " + std::string(e.what()));
        return false;
    }

    if (stmt) sqlite3_finalize(stmt);
    return false;
}