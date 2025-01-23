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
        Media(int id, std::string name, std::string path);
        ~Media() = default;

        // ======= Getters =======

        int getId() const;
        std::string getName() const;
        std::string getPath() const;
        size_t getFileSize() const;
        std::string getType() const;

        // ======= Setters =======

        void setId(int id);
        void setName(std::string name);
        void setPath(std::string path);
        void setFileSize(size_t file_size);
        void setType(std::string type);

        // ======= Methods =======

        void updateMedia(int id, std::string name, std::string path);
};

#endif // MEDIA_H