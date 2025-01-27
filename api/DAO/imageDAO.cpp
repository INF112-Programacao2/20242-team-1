#include "ImageDAO.h"

ImageDAO::ImageDAO(DatabaseConnection& database): db(database){}

Image ImageDAO::getImageById(int id) {
    Image image;  // Objeto vazio para retorno padrão caso não encontre nada
    std::string sql = "SELECT id, width, height, caption, name, path, type, file_size FROM images WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
        }

        sqlite3_bind_int(stmt, 1, id);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            image.setId(sqlite3_column_int(stmt, 0));
            image.setWidth(sqlite3_column_int(stmt, 1));
            image.setHeight(sqlite3_column_int(stmt, 2));

            const char* captionText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            image.setCaption(captionText ? captionText : "");

            const char* nameText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
            image.setName(nameText ? nameText : "");

            const char* pathText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
            image.setPath(pathText ? pathText : "");

            const char* typeText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
            image.setType(typeText ? typeText : "");

            image.setFileSize(sqlite3_column_int(stmt, 7));

            
        } else {
            throw std::invalid_argument("Erro ao executar consulta: Não foi possível encontrar Image com este ID.");
        }
    } catch (const std::exception& e) {
        if (stmt) {
        sqlite3_finalize(stmt);
        }
        throw std::runtime_error("Exceção capturada em getImageById: " + std::string(e.what()));
    }

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    return image;
}

bool ImageDAO::createImage(Image& image){
    std::string sql = "INSERT INTO images (width, height, caption, name, path, type, file_size) VALUES (?, ?, ?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
        }

        // Vincula os valores
        sqlite3_bind_int(stmt, 1, image.getWidth());
        sqlite3_bind_int(stmt, 2, image.getHeight());
        sqlite3_bind_text(stmt, 3, image.getCaption().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, image.getName().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, image.getPath().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 6, image.getType().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 7, image.getFileSize());

        // Executa a consulta
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw std::runtime_error("Erro ao executar consulta: " + db.getLastError());
        }

        // Obtém o ID do Deck recém-criado
        int newId = sqlite3_last_insert_rowid(db.getDB());
        image.setId(newId);  // Atualiza o objeto Deck com o novo ID

        sqlite3_finalize(stmt);
        return true;
    } catch (const std::exception& e) {
        if (stmt) {
        sqlite3_finalize(stmt);
        }
         throw std::runtime_error("Erro em createImage: " + std::string(e.what()));
    }

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    return true;
}
bool ImageDAO::updateImage(Image& image) {
    std::string sql = "UPDATE images SET width = ?, height = ?, caption = ?, name = ?, path = ?, type = ?, file_size = ? WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta de atualização: " + db.getLastError());
        }

        sqlite3_bind_int(stmt, 1, image.getWidth());
        sqlite3_bind_int(stmt, 2, image.getHeight());
        sqlite3_bind_text(stmt, 3, image.getCaption().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, image.getName().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, image.getPath().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 6, image.getType().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 7, image.getFileSize());
        sqlite3_bind_int(stmt, 8, image.getId());

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw std::runtime_error("Erro ao atualizar Image: " + db.getLastError());
        }

        if (sqlite3_changes(db.getDB()) == 0) {
            throw std::runtime_error("Erro: Nenhum Image foi atualizado, possivelmente o ID fornecido não existe.");
        }

        sqlite3_finalize(stmt);
        return true;
    } catch (const std::exception& e) {
        if (stmt) sqlite3_finalize(stmt);
        throw std::runtime_error("Erro em updateImage: " + std::string(e.what()));
        return false;
    }

    if (stmt) sqlite3_finalize(stmt);
    return false;
}
bool ImageDAO::deleteImage(int id) {
    std::string sql = "DELETE FROM images WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta de exclusão: " + db.getLastError());
        }

        sqlite3_bind_int(stmt, 1, id);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw std::runtime_error("Erro ao excluir Image: " + db.getLastError());
        }

        if (sqlite3_changes(db.getDB()) == 0) {
            throw std::runtime_error("Erro: Nenhum Image foi atualizado, possivelmente o ID fornecido não existe.");
        }

        sqlite3_finalize(stmt);
        return true;
    } catch (const std::exception& e) {
        if (stmt) sqlite3_finalize(stmt);
        throw std::runtime_error("Erro em deleteImage: " + std::string(e.what()));
        return false;
    }

    if (stmt) sqlite3_finalize(stmt);
    return false;
}