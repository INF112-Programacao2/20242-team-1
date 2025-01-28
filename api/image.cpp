#include "image.h"
#include <iostream>

Image::Image() {};
Image::Image(int width_, int height_, std::string name_, std::string caption_, std::string path_)
    : width(width_), height(height_), Media(name_, path_), caption(caption_) {
    this->id = -1;
};

// ======= Getters =======

int Image::getId() const
{
    return this->id;
};
int Image::getWidth() const
{
    return this->width;
};
int Image::getHeight() const
{
    return this->height;
};
std::string Image::getCaption() const
{
    return this->caption;
};

// ======= Setters =======

void Image::setId(int id)
{
    this->id = id;
};
void Image::setWidth(int width)
{
    this->width = width;
};
void Image::setHeight(int height)
{
    this->height = height;
};
void Image::setCaption(const std::string &caption)
{
    this->caption = caption;
};

// ======= Methods =======

void Image::updateImage(int id, const std::string &name, const std::string &path)
{
    this->id = id;
    this->width = width;
    this->height = height;
    this->caption = caption;
};

/*
 * @brief Método para exibir a resolução da imagem (formato "largura x altura")
 */
void Image::showResolution()
{
    std::cout << "Resolution: " << this->width << "x" << this->height << std::endl;
}