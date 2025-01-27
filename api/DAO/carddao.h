#ifndef CARDDAO_H
#define CARDDAO_H

#include "../card.h"
#include "DatabaseConnection.h"
#include "deckdao.h"
#include "../date.h"

#include <algorithm>

class CardDAO{
private:
    DatabaseConnection &db;

    void SortDate(std::vector<Card>& cards); //ORGANIZA UM VECTOR DE CARDS PELA DATA 

public:

    CardDAO(DatabaseConnection& database);  //CRIA A CLASSE E INICIA O DATABASE

    bool cardExists(int id);                //BOOL QUE CHECA SE O ID DA CARTA ESCOLHIDA EXISTE; SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    int countCards();                       //CONTA QUANTAS CARTAS TEM EM TODO O DATABASE; SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    int countCardsByDeck(int deck_id);      //CONTA QUANTAS CARTAS TEM EM UM DECK ESPECIFICO; ; SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error

    int getCardIdByCard(Card& card);         //OLHA O FRONT E BACK DE UMA CARTA E RETORNA O ID DELA; SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error; SE NAO EXISTIR A CARTA IRA LANCAR std::invalid_argument
    Card getCardById(int id);               //OLHA O ID FORNECIDO E RETORNA UM CARD;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error; SE NAO EXISTIR O ID IRA LANCAR std::invalid_argument
    Card getCardByDate(Date date);          //OLHA A DATA FORNECIDA E RETORNA UM CARD;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error; SE NAO EXISTIR A DATA IRA LANCAR std::invalid_argument
    Date getDateByCardId(int card_id);//OLHA O ID DA CARTA E RETORNA O lastReview;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error; SE NAO EXISTIR O ID IRA LANCAR std::invalid_argument

    std::vector<Card> getAllCards(); //RETORNA UM VECTOR COM TODAS AS CARTAS NOS DADOS;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    std::vector<Card> getAllCardsSortedByDate();
    std::vector<Card> getCardsByDeckId(int deck_id); // OLHA O ID FORNECIDO E RETORNA UM VECTOR COM TODAS AS CARTAS DESSE DECK;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    std::vector<Card> getCardsByDeckIdSortedByDate(int deck_id);// OLHA O ID FORNECIDO E RETORNA UM VECTOR COM TODAS AS CARTAS DESSE DECK ORDENADAS PELA DATA;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    

    bool createCard(Card& card);//USA A CARTA FORNECIDA PARA CRIAR UMA NOVA, O NOVO ID SERA COLOCADO NA CARTA FORNECIDA E RETORNA SE A OPERAÇÂO OCORREU;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    bool updateCard(const Card& card);//USA A CARTA FORNECIDA PARA EDITAR UMA EXISTENTE, O ID DA CARTA FORNECIDA SERA O USADO PARA EDITAR A CARTA EQUIVALENTE E RETORNA SE A OPERAÇÂO OCORREU;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    bool deleteCard(int id);//USA O ID FORNECIDO PARA DELETAR UMA EXISTENTE E RETORNA SE A OPERAÇÂO OCORREU;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    
    bool deleteCardsByDeckId(int deck_id);//USA O ID DO DECK FORNECIDO PARA DELETAR TODOS OS CARDS COM ESSE deck_id ;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    

    //std::vector<Card> searchCardsByFront(const std::string& front);

};

#endif