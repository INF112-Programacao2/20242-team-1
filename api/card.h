#ifndef CARD_H
#define CARD_H

#include <string>
#include "date.h"

class Card{
    private:
        int id;                     // Identificador
        std::string front;          // Frente da carta
        std::string back;           // Verso da carta
        int deck_id;                // Baralho ao qual a carta pertence
        Date lastReview;            // Última vez que a carta foi estudada

    public:
        Card();
        Card(std::string front, std::string back, int deck_id);
        ~Card() = default;

        // ======= Getters =======

        int getId() const;
        std::string getFront() const;
        std::string getBack() const;
        int getDeckId() const;
        Date getLastReview() const;

        // ======= Setters =======

        void setId(int id);
        void setFront(std::string front);
        void setBack(std::string back);
        void setDeckId(int deck_id);
        void setLastReview(Date lastReview);

        // ======= Methods =======

        void updateCard(std::string front, std::string back, int deck_id);
        // virtual void setNextReview(int levelTime_id, Date lastReview) = 0;
        // virtual void setNextReview() = 0;
        // virtual LevelTime getNextLevelTime() = 0;


}; 

#endif // CARD_H