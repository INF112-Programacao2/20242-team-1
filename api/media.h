#ifndef MEDIA_H
#define MEDIA_H

#include <cstddef>
#include <string>

class Media {
private:
    int id;                     // Identificador
    std::string name;           // Nome da mídia
    std::string path;           // Caminho da mídia
    std::string type;           // Tipo da mídia
    size_t file_size;           // Tamanho do arquivo

public:
    Media();
    Media(std::string name_, std::string path_);
    ~Media() = default;

    // ======= Getters =======

    int getId() const;
    std::string getName() const;
    std::string getPath() const;
    size_t getFileSize() const;
    virtual std::string getType();
    virtual std::string pathName();
    // ======= Setters =======

    void setId(int id);
    void setName(const std::string& name);
    void setPath(const std::string& path);
    void setFileSize(size_t file_size);
    void setType(const std::string& type);

    // ======= Methods =======
    
    void updateMedia(int id, const std::string& name, const std::string& path);
};

#endif // MEDIA_H