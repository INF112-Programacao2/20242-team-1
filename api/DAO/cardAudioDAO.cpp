
#include "cardAudioDAO.h"

CardAudioDAO::CardAudioDAO(DatabaseConnection& database) : db(database) {} 

void CardAudioDAO::SortDate(std::vector<CardAudio>& cards) {
    std::sort(cards.begin(), cards.end(), [](const Card& a, const Card& b) {
        return a.getLastReview().getDateBystring() < b.getLastReview().getDateBystring();
    });
}

bool CardAudioDAO::cardAudioExists(int id) {
    bool exists = false;
    std::string sql = "SELECT COUNT(*) FROM cardsaudio WHERE id = ?;";
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
        throw std::runtime_error("Erro em cardaudioExists: " + std::string(e.what()));
    }
    if (stmt) {
        sqlite3_finalize(stmt);
    }

    return exists;
}

int CardAudioDAO::countCardsAudio() {
    int count = 0;
    std::string sql = "SELECT COUNT(*) FROM cardsaudio;";
    sqlite3_stmt* stmt = nullptr;

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
        }

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            count = sqlite3_column_int(stmt, 0);
        } else {
            throw std::runtime_error("Erro ao executar consulta: " + db.getLastError());
        }
    } catch (const std::exception& e) {
        if (stmt) {
        sqlite3_finalize(stmt);
        }
        throw std::runtime_error("Erro em countCardsAudio: " + std::string(e.what()));
    }
    if (stmt) {
        sqlite3_finalize(stmt);
    }

    return count;
}

int CardAudioDAO::countCardsAudioByDeck(int deck_id) {
    Date date;
    int count = 0;
    std::string sql = "SELECT COUNT(*) FROM cardsaudio WHERE lastReview < ? AND deck_id = ?;";
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
            sqlite3_finalize(stmt);  // Liberação do recurso no caso de erro
        }
        throw std::runtime_error("Exceção capturada em countCardsAudioByDeck: " + std::string(e.what()));
    }
    if (stmt) {
        sqlite3_finalize(stmt);  // Garante a liberação de recursos sempre
    }
    return count;
}


int CardAudioDAO::getCardAudioIdByCardAudio(CardAudio& card){
    int card_id = -1;  // Valor padrão para indicar erro caso não encontre

    std::string sql = "SELECT id FROM cardsaudio WHERE front = ? AND back = ?;";
    sqlite3_stmt* stmt = nullptr;

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
        }

        sqlite3_bind_text(stmt, 1, card.getFront().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, card.getBack().c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            card_id = sqlite3_column_int(stmt, 0);
        } else {
            throw std::invalid_argument("Erro ao executar consulta: Não foi possível encontrar o cardAudio com esse nome e assunto.");
        }
    } catch (const std::exception& e) {
        if (stmt) {
        sqlite3_finalize(stmt);
        }
        throw std::runtime_error("Exceção capturada em getCardIdByCardAudio: " + std::string(e.what()));
    }

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    return card_id;
}
int CardAudioDAO::getAudioIdByCardAudioId(int card_id){
    int audio_id = -1;  // Valor padrão para indicar erro caso não encontre

    std::string sql = "SELECT audio_id FROM cardsaudio WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
        }

        sqlite3_bind_int(stmt,1,card_id);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            audio_id = sqlite3_column_int(stmt, 0);
        } else {
            throw std::invalid_argument("Erro ao executar consulta: Não foi possível encontrar o cardAudio com esse id.");
        }
    } catch (const std::exception& e) {
        if (stmt) {
        sqlite3_finalize(stmt);
        }
        throw std::runtime_error("Exceção capturada em getCardIdByCardAudio: " + std::string(e.what()));
    }

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    return audio_id;
}

CardAudio CardAudioDAO::getCardAudioById(int id) {
    CardAudio card;  // Objeto vazio para retorno padrão caso não encontre nada
    std::string sql = "SELECT id, front, back, deck_id, lastReview, audio_id FROM cardsaudio WHERE id = ?;";
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
            
            card.setAudioId(sqlite3_column_int(stmt, 5));
            
            AudioDAO a(db);
            card.setAudio(a.getAudioById(card.getAudioId()));

        } else {
            throw std::invalid_argument("Erro ao executar consulta: Não foi possível encontrar CardAudio com este ID.");
        }
    } catch (const std::exception& e) {
        if (stmt) {
        sqlite3_finalize(stmt);
        }
        throw std::runtime_error("Exceção capturada em getCardAudioById: " + std::string(e.what()));
    }

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    return card;
}
CardAudio CardAudioDAO::getCardAudioByDate(Date date){
    CardAudio card;
    std::string sql = "SELECT id, front, back, deck_id, lastReview, audio_id FROM cardsaudio WHERE lastReview = ?;";
    sqlite3_stmt* stmt = nullptr;

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
        }

        if (sqlite3_bind_text(stmt, 1, date.getDateBystring().c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK) {
            throw std::runtime_error("Erro ao vincular data na consulta SQL.");
        }

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
            }else {
                throw std::runtime_error("Erro ao obter valor da coluna lastReview.");
            }

            card.setAudioId(sqlite3_column_int(stmt, 5));
            
            AudioDAO a(db);
            card.setAudio(a.getAudioById(card.getAudioId()));
        } else {
             throw std::invalid_argument("Nenhum CardAudio encontrado com a data fornecida.");
        }
    } catch (const std::exception& e) {
        if (stmt) {
        sqlite3_finalize(stmt);
        }
         throw std::runtime_error("Erro em getCardAudioByDate: " + std::string(e.what()));
    }

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    return card;
}
Date CardAudioDAO::getDateByCardAudioId(int card_id){
    Date date;  // Objeto vazio para retorno padrão caso não encontre nada
    std::string sql = "SELECT lastReview FROM cardsaudio WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
        }

        if (sqlite3_bind_int(stmt, 1, card_id) != SQLITE_OK) {
            throw std::runtime_error("Erro ao vincular card_id na consulta SQL.");
        }

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const char* lastReviewText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            if (lastReviewText) {
                date.setDateBystring(lastReviewText);
            } else {
                throw std::runtime_error("Erro ao obter valor da coluna lastReview.");
            }
        } else {
            throw std::invalid_argument("Erro ao executar consulta: Não foi possível encontrar cardaudio com este ID.");
        }
    } catch (const std::exception& e) {
        if (stmt) {
        sqlite3_finalize(stmt);
        }
        throw std::runtime_error("Exceção capturada em getDateByCardAudioId: " + std::string(e.what()));
    }

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    return date;
}

std::vector<CardAudio> CardAudioDAO::getAllCardsAudio(){
    std::vector<CardAudio> cards;
    std::string sql = "SELECT id, front, back, deck_id, lastReview, audio_id FROM cardsaudio;";
    sqlite3_stmt* stmt = nullptr;
    AudioDAO a(db);

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
        }
        
        while (sqlite3_step(stmt) == SQLITE_ROW){
            CardAudio card;

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

            card.setAudioId(sqlite3_column_int(stmt, 5));
            
            card.setAudio(a.getAudioById(card.getAudioId()));

            cards.push_back(card);
        }
    } catch (const std::exception& e) {
        if (stmt) {
        sqlite3_finalize(stmt);
        }
         throw std::runtime_error("Erro em getAllCardsAudio: " + std::string(e.what()));
    }

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    return cards;
}
std::vector<CardAudio> CardAudioDAO::getAllCardsAudioSortedByDate(){
    std::vector<CardAudio> cards;
    cards = getAllCardsAudio();
    
    SortDate(cards);

    return cards;
}
std::vector<CardAudio> CardAudioDAO::getCardsAudioByDeckId(int deck_id){
    std::vector<CardAudio> cards;
    std::string sql = "SELECT id, front, back, deck_id, lastReview, audio_id FROM cardsaudio WHERE deck_id = ?;";
    sqlite3_stmt* stmt = nullptr;
    AudioDAO a(db);

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
        }

        if (sqlite3_bind_int(stmt, 1, deck_id) != SQLITE_OK) {
            throw std::runtime_error("Erro ao vincular o parâmetro deck_id.");
        }

        while (sqlite3_step(stmt) == SQLITE_ROW){
                CardAudio card;

                card.setId(sqlite3_column_int(stmt, 0));

                const char* frontText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                card.setFront(frontText ? frontText : "");

                const char* backText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
                card.setBack(backText ? backText : "");

                card.setDeckId(sqlite3_column_int(stmt, 3));

                const char* lastReviewText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
                if (lastReviewText) {
                    Date b;
                    b.setDateBystring(lastReviewText);
                    card.setLastReview(b);
                }
                card.setAudioId(sqlite3_column_int(stmt, 5));
            
                card.setAudio(a.getAudioById(card.getAudioId()));

                cards.push_back(card);
            }
    } catch (const std::exception& e) {
        if (stmt) {
        sqlite3_finalize(stmt);
        }
         throw std::runtime_error("Erro em getCardsAudioByDeckId: " + std::string(e.what()));
    }

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    return cards;
}
std::vector<CardAudio> CardAudioDAO::getCardsAudioByDeckIdSortedByDate(int deck_id){
    std::vector<CardAudio> cards;
    cards = getCardsAudioByDeckId(deck_id);
    
    SortDate(cards);

    return cards;
}
std::vector<CardAudio> CardAudioDAO::getCardsAudioByDate(const Date date,int deck_id) {
    std::vector<CardAudio> cards;
    std::string sql = "SELECT id, front, back, deck_id, lastReview, audio_id FROM cardsaudio WHERE lastReview < ? AND deck_id = ?;";
    sqlite3_stmt* stmt = nullptr;
    AudioDAO a(db);

    try {
        // Prepara a consulta SQL
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
        }
        sqlite3_bind_text(stmt, 1, date.getDateBystring().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, deck_id);

        if (sqlite3_step(stmt) != SQLITE_ROW) {
            throw std::runtime_error("Erro ao vincular data na consulta SQL.");

        }

        // Itera sobre os resultados
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            CardAudio card;

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

            card.setAudioId(sqlite3_column_int(stmt, 5));
            
            card.setAudio(a.getAudioById(card.getAudioId()));

            // Adiciona o card ao vetor
            cards.push_back(card);
        }
    } catch (const std::exception& e) {
        if (stmt) {
            sqlite3_finalize(stmt);
        }
        throw std::runtime_error("Erro em getCardsAudioByDate: " + std::string(e.what()));
    }

    // Finaliza o statement
    if (stmt) {
        sqlite3_finalize(stmt);
    }

    return cards;
}
    

int CardAudioDAO::createCardAudio(CardAudio& card){
    std::string sql = "INSERT INTO cardsaudio (front, back, deck_id, lastReview, audio_Id) VALUES (?, ?,?,?,?);";
    sqlite3_stmt* stmt = nullptr;
    AudioDAO a(db);

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consultaaa: " + db.getLastError());
        }

        // Vincula os valores
        a.createAudio(card.getAudio());
        card.setAudioId(card.getAudio().getId());
        if (sqlite3_bind_text(stmt, 1, card.getFront().c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK ||
            sqlite3_bind_text(stmt, 2, card.getBack().c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK ||
            sqlite3_bind_int(stmt, 3, card.getDeckId()) != SQLITE_OK ||
            sqlite3_bind_text(stmt, 4, card.getLastReview().getDateBystring().c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK ||
            sqlite3_bind_int(stmt, 5, card.getAudioId()) != SQLITE_OK) {
            throw std::runtime_error("Erro ao vincular parâmetros à consulta SQL.");
        }

        // Executa a consulta
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw std::runtime_error("Erro ao executar consulta: " + db.getLastError());
        }

        // Obtém o ID do Deck recém-criado
        int newId = sqlite3_last_insert_rowid(db.getDB());
        card.setId(newId);  // Atualiza o objeto Deck com o novo ID

        card.setAudioId(card.getAudio().getId());

        sqlite3_finalize(stmt);
        return newId;
    } catch (const std::exception& e) {
        if (stmt) {
        sqlite3_finalize(stmt);
        }
         throw std::runtime_error("Erro em createCardAudio: " + std::string(e.what()));
    }

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    return 0;
}
bool CardAudioDAO::updateCardAudio(CardAudio& card) {
    std::string sql = "UPDATE cardsaudio SET front = ?, back = ?, deck_id = ?, lastReview = ? WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;
    AudioDAO a(db);

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta de atualização: " + db.getLastError());
        }

        if (sqlite3_bind_text(stmt, 1, card.getFront().c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK ||
            sqlite3_bind_text(stmt, 2, card.getBack().c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK ||
            sqlite3_bind_int(stmt, 3, card.getDeckId()) != SQLITE_OK ||
            sqlite3_bind_text(stmt, 4, card.getLastReview().getDateBystring().c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK ||
            sqlite3_bind_int(stmt, 5, card.getId()) != SQLITE_OK) {
            throw std::runtime_error("Erro ao vincular parâmetros à consulta SQL.");
        }

        if (!(a.updateAudio(card.getAudio()))) {
            throw std::runtime_error("Erro ao atualizar a audiom associada ao card.");
        }

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw std::runtime_error("Erro ao atualizar cardAudio: " + db.getLastError());
        }

        if (sqlite3_changes(db.getDB()) == 0) {
            throw std::runtime_error("Erro: Nenhum cardAudio foi atualizado, possivelmente o ID fornecido não existe.");
        }

        sqlite3_finalize(stmt);
        return true;
    } catch (const std::exception& e) {
        if (stmt) sqlite3_finalize(stmt);
        throw std::runtime_error("Erro em updateCardAudio: " + std::string(e.what()));
        return false;
    }

    if (stmt) sqlite3_finalize(stmt);
    return false;
}
bool CardAudioDAO::deleteCardAudio(int id) {
    std::string sql = "DELETE FROM cardsaudio WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;
    AudioDAO a(db);

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta de exclusão: " + db.getLastError());
        }

        sqlite3_bind_int(stmt, 1, id);

        if(!(a.deleteAudio(getAudioIdByCardAudioId(id)))){
            throw std::runtime_error("Erro ao excluir Audiom: " + db.getLastError());
        }

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw std::runtime_error("Erro ao excluir cardAudio: " + db.getLastError());
        }

        if (sqlite3_changes(db.getDB()) == 0) {
            throw std::runtime_error("Erro: Nenhum cardAudio foi atualizado, possivelmente o ID fornecido não existe.");
        }

        sqlite3_finalize(stmt);
        return true;
    } catch (const std::exception& e) {
        if (stmt) sqlite3_finalize(stmt);
        throw std::runtime_error("Erro em deleteCardAudio: " + std::string(e.what()));
        return false;
    }

    if (stmt) sqlite3_finalize(stmt);
    return false;
}
    
bool CardAudioDAO::deleteCardsAudioByDeckId(int deck_id) {
    std::string sql = "DELETE FROM cardsaudio WHERE deck_id = ?;";
    sqlite3_stmt* stmt = nullptr;
    AudioDAO a(db);

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta de exclusão por deck: " + db.getLastError());
        }

        sqlite3_bind_int(stmt, 1, deck_id);

        if(!(a.deleteAudio(getAudioIdByCardAudioId(deck_id)))){
            throw std::runtime_error("Erro ao excluir Audiom: " + db.getLastError());
        }

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw std::runtime_error("Erro ao excluir cardsAudio do deck: " + db.getLastError());
        }

        if (sqlite3_changes(db.getDB()) == 0) {
            throw std::runtime_error("Erro: Nenhum cardAudio foi atualizado, possivelmente o ID fornecido não existe.");
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