#ifndef IMAGE_H
#define IMAGE_H

#include "media.h"
#include <string>

class Image : Media {
    private:
        int id;                        // Identificador da imagem
        int width;                     // Largura da imagem
        int height;                    // Altura da imagem        
        std::string caption;            // Descrição da imagem
    
    public:
        Image();
        Image(int id, std::string name, std::string path);
        ~Image() = default;

        // ======= Getters =======

        int getId() const;
        int getWidth() const;
        int getHeight() const;
        std::string getCaption() const;

        // ======= Setters =======

        void setId(int id);
        void setWidth(int width);
        void setHeight(int height);
        void setCaption(const std::string& caption);

        // ======= Methods =======

        void updateImage(int id, const std::string& name, const std::string& path);
        void showResolution();
};

#endif