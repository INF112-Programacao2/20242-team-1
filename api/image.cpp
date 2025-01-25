#include "image.h"
#include <iostream>
/*
* @brief Método para exibir a resolução da imagem (formato "largura x altura")
*/
void Image::showResolution() {
    std::cout << "Resolution: " << this->width << "x" << this->height << std::endl;
}