 #include "cardimage.h"

CardImage::CardImage(){};

        // ======= Getters =======

Image CardImage::getImage() const{
    return this->image;
};

        // ======= Setters =======

void CardImage::setImage(const Image& image){
    this->image=image;
};

        // ======= Methods =======

void CardImage::showCard(){};