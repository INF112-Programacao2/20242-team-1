 #include "cardimage.h"

 #include <string>

CardImage::CardImage(){};
CardImage::CardImage( std::string front, std::string back, int deck_id): Card(front,back,deck_id){}

        // ======= Getters =======

Image& CardImage::getImage(){
    return this->image;
};

int CardImage::getImageId(){
        return this->image_id;
}

        // ======= Setters =======

void CardImage::setImage(const Image& image){
    this->image=image;
};
void CardImage::setImageId(int image_id){
        this->image_id = image_id;
}

        // ======= Methods =======

void CardImage::showCard(){};