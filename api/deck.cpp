// deck.cpp
#include "deck.h"

Deck::Deck(){
    this->id = 0;
     this->title ="";
    this->subject = "";
}

Deck::Deck(std::string title, std::string subject){
    this->title = title;
    this->subject = subject;
    //this->cards.fill(Card());
}
Deck::Deck(int id,std::string title, std::string subject){
    this->id = id;
    this->title = title;
    this->subject = subject;
    //this->cards.fill(Card());
}
int Deck::getId() const{
    return this->id;
}

std::string Deck::getTitle() const{
    return this->title;
}

std::string Deck::getSubject() const{
    return this->subject;
}
/*
std::array<Card,50> Deck::getCards() const{
    return this->cards;
}
*/
void Deck::setId(int id){
    this->id = id;
}

void Deck::setTitle(std::string title){
    this->title = title;
}

void Deck::setSubject(std::string subject){
    this->subject = subject;
}

void Deck::updateDeck(std::string title, std::string subject){
    this->title = title;
    this->subject = subject;
}

/*
void Deck::addCard(Card card){
    for (int i = 0; i < 50; i++){
        if (this->cards[i].getId() == -1){
            this->cards[i] = card;
            break;
        }
    }
}

void Deck::removeCard(int id){
    for (int i = 0; i < 50; i++){
        if (this->cards[i].getId() == id){
            this->cards[i] = Card();
            break;
        }
    }
}*/