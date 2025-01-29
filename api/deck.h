#ifndef DECK_H
#define DECK_H

#include <string>
#include <array>
//#include "card.h"

class Deck{
    private:
        int id;                         // Identificador
        std::string title;              // Título
        std::string subject;            // Assunto/matéria
       // std::array<Card,50> cards;      // Cartas do baralho. MÁX: 50

    public:
        // Construtor
        Deck();
        Deck(std::string title, std::string subject);
        Deck(int id,std::string title, std::string subject);
        // Destrutor
        ~Deck() = default;

        // Getters
        int getId() const;
        std::string getTitle() const;
        std::string getSubject() const;
       // std::array<Card,50> getCards() const;

        // Setters
        void setId(int id);
        void setTitle(std::string title);
        void setSubject(std::string subject);

        // Métodos
        void updateDeck(std::string title, std::string subject);
        //void addCard(Card card);
        //void removeCard(int id);

};

#endif // DECK_H