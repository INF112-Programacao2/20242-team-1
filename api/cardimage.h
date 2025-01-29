#ifndef CARDIMAGE_H
#define CARDIMAGE_H

#include "image.h"
#include "card.h"

#include <string>

class CardImage : public Card{

    private:
        Image image; // Imagem do card
        int image_id;

    public:
        CardImage();
        CardImage(std::string front, std::string back, int deck_id);
        ~CardImage() = default;

        // ======= Getters =======

        Image& getImage();
        virtual int getImageId() override;


        // ======= Setters =======

        void setImage(const Image& image);
        void setImageId(int image_id);

        // ======= Methods =======

        void showCard();


};

#endif // CARDIMAGE_H