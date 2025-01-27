#include "audioDAO.h"

AudioDAO::AudioDAO(DatabaseConnection& database): db(database){}

Audio AudioDAO::getAudioById(int id) {
    Audio audio;  // Objeto vazio para retorno padrão caso não encontre nada
    std::string sql = "SELECT id, name, path, type, file_size, durationInSeconds, transcription FROM audio WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
        }

        sqlite3_bind_int(stmt, 1, id);

        if (sqlite3_step(stmt) == SQLITE_ROW) {
            audio.setId(sqlite3_column_int(stmt, 0));

            const char* nameText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            audio.setName(nameText ? nameText : "");

            const char* pathText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            audio.setPath(pathText ? pathText : "");

            const char* typeText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            audio.setType(typeText ? typeText : "");

            audio.setFileSize(sqlite3_column_int(stmt, 4));
            audio.setDurationInSeconds(sqlite3_column_int(stmt, 5));

            const char* captionText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
            audio.setTranscription(captionText ? captionText : "");

            
        } else {
            throw std::invalid_argument("Erro ao executar consulta: Não foi possível encontrar Audio com este ID.");
        }
    } catch (const std::exception& e) {
        if (stmt) {
        sqlite3_finalize(stmt);
        }
        throw std::runtime_error("Exceção capturada em getAudioById: " + std::string(e.what()));
    }

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    return audio;
}

bool AudioDAO::createAudio(Audio& audio){
    std::string sql = "INSERT INTO audio (name, path, type, file_size, durationInSeconds, transcription) VALUES (?, ?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta: " + db.getLastError());
        }

        // Vincula os valores
        sqlite3_bind_text(stmt, 1, audio.getName().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, audio.getPath().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, audio.getType().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 4, audio.getFileSize());
        sqlite3_bind_double(stmt, 5, audio.getDurationInSeconds());
        sqlite3_bind_text(stmt, 6, audio.getTranscription().c_str(), -1, SQLITE_TRANSIENT);

        // Executa a consulta
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw std::runtime_error("Erro ao executar consulta: " + db.getLastError());
        }

        // Obtém o ID do Deck recém-criado
        int newId = sqlite3_last_insert_rowid(db.getDB());
        audio.setId(newId);  // Atualiza o objeto Deck com o novo ID

        sqlite3_finalize(stmt);
        return true;
    } catch (const std::exception& e) {
        if (stmt) {
        sqlite3_finalize(stmt);
        }
         throw std::runtime_error("Erro em createAudio: " + std::string(e.what()));
    }

    if (stmt) {
        sqlite3_finalize(stmt);
    }
    return true;
}
bool AudioDAO::updateAudio(Audio& audio) {
    std::string sql = "UPDATE audio SET name = ?, path = ?, type = ?, file_size = ?, durationInSeconds = ?, transcription = ? WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta de atualização: " + db.getLastError());
        }

        sqlite3_bind_text(stmt, 1, audio.getName().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, audio.getPath().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, audio.getType().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 4, audio.getFileSize());
        sqlite3_bind_double(stmt, 5, audio.getDurationInSeconds());
        sqlite3_bind_text(stmt, 6, audio.getTranscription().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 7, audio.getId());
        

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw std::runtime_error("Erro ao atualizar Audio: " + db.getLastError());
        }

        if (sqlite3_changes(db.getDB()) == 0) {
            throw std::runtime_error("Erro: Nenhum Audio foi atualizado, possivelmente o ID fornecido não existe.");
        }

        sqlite3_finalize(stmt);
        return true;
    } catch (const std::exception& e) {
        if (stmt) sqlite3_finalize(stmt);
        throw std::runtime_error("Erro em updateAudio: " + std::string(e.what()));
        return false;
    }

    if (stmt) sqlite3_finalize(stmt);
    return false;
}
bool AudioDAO::deleteAudio(int id) {
    std::string sql = "DELETE FROM audio WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;

    try {
        if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            throw std::runtime_error("Erro ao preparar consulta de exclusão: " + db.getLastError());
        }

        sqlite3_bind_int(stmt, 1, id);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            throw std::runtime_error("Erro ao excluir Audio: " + db.getLastError());
        }

        if (sqlite3_changes(db.getDB()) == 0) {
            throw std::runtime_error("Erro: Nenhum Audio foi atualizado, possivelmente o ID fornecido não existe.");
        }

        sqlite3_finalize(stmt);
        return true;
    } catch (const std::exception& e) {
        if (stmt) sqlite3_finalize(stmt);
        throw std::runtime_error("Erro em deleteAudio: " + std::string(e.what()));
        return false;
    }

    if (stmt) sqlite3_finalize(stmt);
    return false;
}