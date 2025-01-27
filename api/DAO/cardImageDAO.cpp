
#include "cardImageDAO.h"

CardImageDAO::CardImageDAO(DatabaseConnection& database) : db(database) {} 

void CardImageDAO::SortDate(std::vector<CardImage>& cards) {
    std::sort(cards.begin(), cards.end(), [](const Card& a, const Card& b) {
        return a.getLastReview().getDateBystring() < b.getLastReview().getDateBystring();
    });
}

bool CardImageDAO::cardImageExists(int id) {
    bool exists = false;
    std::string sql = "SELECT COUNT(*) FROM cardsimage WHERE id = ?;";
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
        throw std::runtime_error("Erro em cardimageExists: " + std::string(e.what()));
    }
    if (stmt) {
        sqlite3_finalize(stmt);
    }

    return exists;
}

int CardImageDAO::countCardsImage() {
    int count = 0;
    std::string sql = "SELECT COUNT(*) FROM cardsimage;";
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
        throw std::runtime_error("Erro em countCardsImage: " + std::string(e.what()));
    }
    if (stmt) {
        sqlite3_finalize(stmt);
    }

    return count;
}

int CardImageDAO::countCardsImageByDeck(int deck_id) {
    int count = 0;
    std::string sql = "SELECT COUNT(*) FROM cardsimage WHERE deck_id = ?;";
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
        throw std::runtime_error("Exceção capturada em countCardsImageByDeck: " + std::string(e.what()));
    }
    if (stmt) {
        sqlite3_finalize(stmt);  // Garante a liberação de recursos sempre
    }
    return count;
}


int CardImageDAO::getCardImageIdByCardImage(CardImage& card){
    int card_id = -1;  // Valor padrão para indicar erro caso não encontre

    std::string sql = "SELECT id FROM cardsimage WHERE front = ? AND back = ?;";
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
            throw std::invalid_argument("Erro ao executar consulta: Não foi possível encontrar o cardImage com esse nome e assunto.");
        }
    } catch (const std::exception& e) {
        if (stmt) {
        sqlite3_finalize(stmt);
        }
        throw std::runtime_error("Exceção capturada em getCardIdByCardImage: " + std::string(e.what()));
    }

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    return card_id;
}
int CardImageDAO::getImageIdByCardImageId(int card_id){
    int image_id = -1;  // Valor padrão para indicar erro caso não encontre

    std::string sql = "SELECT imageId FROM cardsimage WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
        }

        sqlite3_bind_int(stmt,1,card_id);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            image_id = sqlite3_column_int(stmt, 0);
        } else {
            throw std::invalid_argument("Erro ao executar consulta: Não foi possível encontrar o cardImage com esse id.");
        }
    } catch (const std::exception& e) {
        if (stmt) {
        sqlite3_finalize(stmt);
        }
        throw std::runtime_error("Exceção capturada em getCardIdByCardImage: " + std::string(e.what()));
    }

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    return image_id;
}

CardImage CardImageDAO::getCardImageById(int id) {
    CardImage card;  // Objeto vazio para retorno padrão caso não encontre nada
    std::string sql = "SELECT id, front, back, deck_id, lastReview, imageId FROM cardsimage WHERE id = ?;";
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
            
            card.setImageId(sqlite3_column_int(stmt, 5));
            
            ImageDAO a(db);
            card.setImage(a.getImageById(card.getImageId()));

        } else {
            throw std::invalid_argument("Erro ao executar consulta: Não foi possível encontrar CardImage com este ID.");
        }
    } catch (const std::exception& e) {
        if (stmt) {
        sqlite3_finalize(stmt);
        }
        throw std::runtime_error("Exceção capturada em getCardImageById: " + std::string(e.what()));
    }

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    return card;
}
CardImage CardImageDAO::getCardImageByDate(Date date){
    CardImage card;
    std::string sql = "SELECT id, front, back, deck_id, lastReview, imageId FROM cardsimage WHERE lastReview = ?;";
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

            card.setImageId(sqlite3_column_int(stmt, 5));
            
            ImageDAO a(db);
            card.setImage(a.getImageById(card.getImageId()));
        } else {
             throw std::invalid_argument("Nenhum CardImage encontrado com a data fornecida.");
        }
    } catch (const std::exception& e) {
        if (stmt) {
        sqlite3_finalize(stmt);
        }
         throw std::runtime_error("Erro em getCardImageByDate: " + std::string(e.what()));
    }

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    return card;
}
Date CardImageDAO::getDateByCardImageId(int card_id){
    Date date;  // Objeto vazio para retorno padrão caso não encontre nada
    std::string sql = "SELECT lastReview FROM cardsimage WHERE id = ?;";
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
            throw std::invalid_argument("Erro ao executar consulta: Não foi possível encontrar cardimage com este ID.");
        }
    } catch (const std::exception& e) {
        if (stmt) {
        sqlite3_finalize(stmt);
        }
        throw std::runtime_error("Exceção capturada em getDateByCardImageId: " + std::string(e.what()));
    }

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    return date;
}

std::vector<CardImage> CardImageDAO::getAllCardsImage(){
    std::vector<CardImage> cards;
    std::string sql = "SELECT id, front, back, deck_id, lastReview, imageId FROM cardsimage;";
    sqlite3_stmt* stmt = nullptr;
    ImageDAO a(db);

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
        }
        
        while (sqlite3_step(stmt) == SQLITE_ROW){
            CardImage card;

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

            card.setImageId(sqlite3_column_int(stmt, 5));
            
            card.setImage(a.getImageById(card.getImageId()));

            cards.push_back(card);
        }
    } catch (const std::exception& e) {
        if (stmt) {
        sqlite3_finalize(stmt);
        }
         throw std::runtime_error("Erro em getAllCardsImage: " + std::string(e.what()));
    }

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    return cards;
}
std::vector<CardImage> CardImageDAO::getAllCardsImageSortedByDate(){
    std::vector<CardImage> cards;
    cards = getAllCardsImage();
    
    SortDate(cards);

    return cards;
}
std::vector<CardImage> CardImageDAO::getCardsImageByDeckId(int deck_id){
    std::vector<CardImage> cards;
    std::string sql = "SELECT id, front, back, deck_id, lastReview, imageId FROM cardsimage WHERE deck_id = ?;";
    sqlite3_stmt* stmt = nullptr;
    ImageDAO a(db);

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
        }

        if (sqlite3_bind_int(stmt, 1, deck_id) != SQLITE_OK) {
            throw std::runtime_error("Erro ao vincular o parâmetro deck_id.");
        }

        while (sqlite3_step(stmt) == SQLITE_ROW){
                CardImage card;

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
                card.setImageId(sqlite3_column_int(stmt, 5));
            
                card.setImage(a.getImageById(card.getImageId()));

                cards.push_back(card);
            }
    } catch (const std::exception& e) {
        if (stmt) {
        sqlite3_finalize(stmt);
        }
         throw std::runtime_error("Erro em getCardsImageByDeckId: " + std::string(e.what()));
    }

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    return cards;
}
std::vector<CardImage> CardImageDAO::getCardsImageByDeckIdSortedByDate(int deck_id){
    std::vector<CardImage> cards;
    cards = getCardsImageByDeckId(deck_id);
    
    SortDate(cards);

    return cards;
}
std::vector<CardImage> CardImageDAO::getCardsByDate(const Date date,int deck_id) {
    std::vector<CardImage> cards;
    std::string sql = "SELECT id, front, back, deck_id, lastReview, imageId FROM cardsimage WHERE lastReview = ? AND deck_id = ?;";
    sqlite3_stmt* stmt = nullptr;
    ImageDAO a(db);

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
            CardImage card;

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

            card.setImageId(sqlite3_column_int(stmt, 5));
            
            card.setImage(a.getImageById(card.getImageId()));

            // Adiciona o card ao vetor
            cards.push_back(card);
        }
    } catch (const std::exception& e) {
        if (stmt) {
            sqlite3_finalize(stmt);
        }
        throw std::runtime_error("Erro em getCardsImageByDate: " + std::string(e.what()));
    }

    // Finaliza o statement
    if (stmt) {
        sqlite3_finalize(stmt);
    }

    return cards;
}
    

bool CardImageDAO::createCardImage(CardImage& card){
    std::string sql = "INSERT INTO cardsimage (front, back, deck_id, lastReview, imageId) VALUES (?, ?,?,?,?);";
    sqlite3_stmt* stmt;
    ImageDAO a(db);

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consultaaa: " + db.getLastError());
        }

        // Vincula os valores
        a.createImage(card.getImage());
        card.setImageId(card.getImage().getId());
        if (sqlite3_bind_text(stmt, 1, card.getFront().c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK ||
            sqlite3_bind_text(stmt, 2, card.getBack().c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK ||
            sqlite3_bind_int(stmt, 3, card.getDeckId()) != SQLITE_OK ||
            sqlite3_bind_text(stmt, 4, card.getLastReview().getDateBystring().c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK ||
            sqlite3_bind_int(stmt, 5, card.getImageId()) != SQLITE_OK) {
            throw std::runtime_error("Erro ao vincular parâmetros à consulta SQL.");
        }

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
         throw std::runtime_error("Erro em createCardImage: " + std::string(e.what()));
    }

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    return true;
}
bool CardImageDAO::updateCardImage(CardImage& card) {
    std::string sql = "UPDATE cardsimage SET front = ?, back = ?, deck_id = ?, lastReview = ? WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;
    ImageDAO a(db);

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

        if (!(a.updateImage(card.getImage()))) {
            throw std::runtime_error("Erro ao atualizar a imagem associada ao card.");
        }

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw std::runtime_error("Erro ao atualizar cardImage: " + db.getLastError());
        }

        if (sqlite3_changes(db.getDB()) == 0) {
            throw std::runtime_error("Erro: Nenhum cardImage foi atualizado, possivelmente o ID fornecido não existe.");
        }

        int newId = sqlite3_last_insert_rowid(db.getDB());
        card.setId(newId);  // Atualiza o objeto Deck com o novo ID

        card.setImageId(card.getImage().getId());

        sqlite3_finalize(stmt);
        return true;
    } catch (const std::exception& e) {
        if (stmt) sqlite3_finalize(stmt);
        throw std::runtime_error("Erro em updateCardImage: " + std::string(e.what()));
        return false;
    }

    if (stmt) sqlite3_finalize(stmt);
    return false;
}
bool CardImageDAO::deleteCardImage(int id) {
    std::string sql = "DELETE FROM cardsimage WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;
    ImageDAO a(db);

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta de exclusão: " + db.getLastError());
        }

        sqlite3_bind_int(stmt, 1, id);

        if(!(a.deleteImage(getImageIdByCardImageId(id)))){
            throw std::runtime_error("Erro ao excluir Imagem: " + db.getLastError());
        }

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw std::runtime_error("Erro ao excluir cardImage: " + db.getLastError());
        }

        if (sqlite3_changes(db.getDB()) == 0) {
            throw std::runtime_error("Erro: Nenhum cardImage foi atualizado, possivelmente o ID fornecido não existe.");
        }

        sqlite3_finalize(stmt);
        return true;
    } catch (const std::exception& e) {
        if (stmt) sqlite3_finalize(stmt);
        throw std::runtime_error("Erro em deleteCardImage: " + std::string(e.what()));
        return false;
    }

    if (stmt) sqlite3_finalize(stmt);
    return false;
}
    
bool CardImageDAO::deleteCardsImageByDeckId(int deck_id) {
    std::string sql = "DELETE FROM cardsimage WHERE deck_id = ?;";
    sqlite3_stmt* stmt = nullptr;
    ImageDAO a(db);

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta de exclusão por deck: " + db.getLastError());
        }

        sqlite3_bind_int(stmt, 1, deck_id);

        if(!(a.deleteImage(getImageIdByCardImageId(deck_id)))){
            throw std::runtime_error("Erro ao excluir Imagem: " + db.getLastError());
        }

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw std::runtime_error("Erro ao excluir cardsImage do deck: " + db.getLastError());
        }

        if (sqlite3_changes(db.getDB()) == 0) {
            throw std::runtime_error("Erro: Nenhum cardImage foi atualizado, possivelmente o ID fornecido não existe.");
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