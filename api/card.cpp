// card.cpp
#include "card.h"

/*
* @brief Construtor da classe Card, que inicia uma carta nula
* @param void
* @return void
*/
Card::Card(){
    this->id = -1;
    this->front = "";
    this->back = "";
}

/*
* @brief Construtor da classe Card, que inicia uma carta com frente, verso e id do baralho
* @param std::string Texto da frente da carta
* @param std::string Texto do verso da carta
* @param int Id do baralho ao qual a carta pertence
* @return void
*/
Card::Card(std::string front, std::string back, int deck_id){
    this->id = -1;
    this->front = front;
    this->back = back;
    this->deck_id = deck_id;
}

/*
* @brief Método que retorna o id da carta
* @param void
* @return int Id da carta
*/
int Card::getId() const{
    return this->id;
}

/*
* @brief Método que retorna o texto da frente da carta
* @param void
* @return std::string Texto da frente da carta
*/
std::string Card::getFront() const{
    return this->front;
}

/*
* @brief Método que retorna o texto do verso da carta
* @param void
* @return std::string Texto do verso da carta
*/
std::string Card::getBack() const{
    return this->back;
}

/*
* @brief Método que retorna o id do baralho ao qual a carta pertence
* @param void
* @return int Id do baralho ao qual a carta pertence
*/
int Card::getDeckId() const{
    return this->deck_id;
}

/*
* @brief Método que retorna o id do nível de tempo ao qual a carta pertence
* @param void
* @return int Id do nível de tempo ao qual a carta pertence
*/
int Card::getLevelTimeId() const{
    return this->levelTime_id;
}

/*
* @brief Método que retorna a data da última revisão da carta
* @param void
* @return Date Data da última revisão da carta
*/
Date Card::getLastReview() const{
    return this->lastReview;
}

/*
* @brief Método que atualiza o id da carta
* @param int Id da carta
* @return void
*/
void Card::setId(int id){
    this->id = id;
}

/*
* @brief Método que atualiza o texto da frente da carta
* @param std::string Texto da frente da carta
* @return void
*/
void Card::setFront(std::string front){
    this->front = front;
}

/*
* @brief Método que atualiza o texto do verso da carta
* @param std::string Texto do verso da carta
* @return void
*/
void Card::setBack(std::string back){
    this->back = back;
}

/*
* @brief Método que atualiza o id do baralho ao qual a carta pertence
* @param int Id do baralho ao qual a carta pertence
* @return void
*/
void Card::setDeckId(int deck_id){
    this->deck_id = deck_id;
}

/*
* @brief Método que atualiza o id do nível de tempo ao qual a carta pertence
* @param int Id do nível de tempo ao qual a carta pertence
* @return void
*/
void Card::setLevelTimeId(int levelTime_id){
    this->levelTime_id = levelTime_id;
}

/*
* @brief Método que atualiza a data da última revisão da carta
* @param Date Data da última revisão da carta
* @return void
*/
void Card::setLastReview(Date lastReview){
    this->lastReview = lastReview;
}

/*
* @brief Método que atualiza o texto da frente, verso e id do baralho da carta
* @param std::string Texto da frente da carta
* @param std::string Texto do verso da carta
* @param int Id do baralho ao qual a carta pertence
* @return void
*/
void Card::updateCard(std::string front, std::string back, int deck_id){
    this->front = front;
    this->back = back;
    this->deck_id = deck_id;
}