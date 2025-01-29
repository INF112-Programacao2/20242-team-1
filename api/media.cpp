#include "media.h"
#include <cstdio>

/*
* @brief Construtor da classe Media, que inicia uma mídia nula
*/
Media::Media() {
    this->id = -1;
    this->name = "";
    this->path = "";
    this->type = "";
    this->file_size = 0;
}

/*
* @brief Construtor da classe Media, que inicia uma mídia com nome, caminho e tamanho do arquivo
* @param id Identificador da mídia
* @param name Nome da mídia
* @param path Caminho da mídia
*/
Media::Media(std::string name, std::string path) {
    this->id = -1;
    this->name = name;
    this->path = path;

    // Detectar tipo de arquivo pela extensão
    size_t dotPos = path.find_last_of(".");
    if (dotPos != std::string::npos) {
        this->type = path.substr(dotPos + 1);
    }

    // Obter tamanho do arquivo
    FILE* file = fopen(path.c_str(), "rb");
    if (file) {
        fseek(file, 0, SEEK_END);
        this->file_size = ftell(file);
        fclose(file);
    } else {
        this->file_size = 0;
    }
}

// Implementação dos Getters

int Media::getId() const { return id; }
std::string Media::getName() const { return name; }
std::string Media::getPath() const { return path; }
size_t Media::getFileSize() const { return file_size; }

// Implementação dos Setters

void Media::setId(int newId) { id = newId; }
void Media::setName(const std::string& newName) { name = newName; }
void Media::setPath(const std::string& newPath) { 
    path = newPath; 
    
    // Atualizar tipo e tamanho quando o caminho muda
    size_t dotPos = path.find_last_of(".");
    if (dotPos != std::string::npos) {
        setType(path.substr(dotPos + 1));
    }

    FILE* file = fopen(path.c_str(), "rb");
    if (file) {
        fseek(file, 0, SEEK_END);
        setFileSize(ftell(file));
        fclose(file);
    } else {
        setFileSize(0);
    }
}
 std::string Media::getType(){
    return type;
 };
 std::string Media::pathName(){
    return path + name;
 };

void Media::setFileSize(size_t newFileSize) { file_size = newFileSize; }
void Media::setType(const std::string& newType) { type = newType; }

// Método para atualizar dados da mídia
void Media::updateMedia(int newId, const std::string& newName, const std::string& newPath) {
    id = newId;
    name = newName;
    setPath(newPath);  // Usando setPath para atualizar automaticamente tipo e tamanho
}