#ifndef CARDIMAGE_H
#define CARDIMAGE_H

#include "image.h"
#include "card.h"

class CardImage : public Card{

    private:
        Image image; // Imagem do card

    public:
        CardImage();
        CardImage(int id, std::string name, std::string path);
        ~CardImage() = default;

        // ======= Getters =======

        Image getImage() const;

        // ======= Setters =======

        void setImage(const Image& image);

        // ======= Methods =======

        void showCard();


};

#endif // CARDIMAGE_H