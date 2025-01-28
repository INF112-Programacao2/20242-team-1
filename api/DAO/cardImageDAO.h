#ifndef CARDIMAGEDAO_H
#define CARDIMAGEDAO_H

#include "../card.h"
#include "DatabaseConnection.h"
#include "deckdao.h"
#include "../date.h"
#include "../cardimage.h"
#include "../image.h"
#include "imageDAO.h"

#include <algorithm>

class CardImageDAO{
private:
    DatabaseConnection &db;

    void SortDate(std::vector<CardImage>& cards); //ORGANIZA UM VECTOR DE CARDS PELA DATA 

public:

    CardImageDAO(DatabaseConnection& database);  //CRIA A CLASSE E INICIA O DATABASE

    bool cardImageExists(int id);                //BOOL QUE CHECA SE O ID DA CARTA ESCOLHIDA EXISTE; SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    int countCardsImage();                       //CONTA QUANTAS CARTAS TEM EM TODO O DATABASE; SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    int countCardsImageByDeck(int deck_id);      //CONTA QUANTAS CARTAS TEM EM UM DECK ESPECIFICO; ; SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error

    int getCardImageIdByCardImage(CardImage& card);         //OLHA O FRONT E BACK DE UMA CARTA E RETORNA O ID DELA; SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error; SE NAO EXISTIR A CARTA IRA LANCAR std::invalid_argument
    int getImageIdByCardImageId(int id);
    CardImage getCardImageById(int id);               //OLHA O ID FORNECIDO E RETORNA UM CARD;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error; SE NAO EXISTIR O ID IRA LANCAR std::invalid_argument
    CardImage getCardImageByDate(Date date);          //OLHA A DATA FORNECIDA E RETORNA UM CARD;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error; SE NAO EXISTIR A DATA IRA LANCAR std::invalid_argument
    Date getDateByCardImageId(int card_id);//OLHA O ID DA CARTA E RETORNA O lastReview;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error; SE NAO EXISTIR O ID IRA LANCAR std::invalid_argument
    Image getImageByCardImageId(int card_id);
    CardImage getCardImageByImage(Image Image);
    std::vector<CardImage> getCardsByDate(int deck_id);

    std::vector<CardImage> getAllCardsImage(); //RETORNA UM VECTOR COM TODAS AS CARTAS NOS DADOS;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    std::vector<CardImage> getAllCardsImageSortedByDate();
    std::vector<CardImage> getCardsImageByDeckId(int deck_id); // OLHA O ID FORNECIDO E RETORNA UM VECTOR COM TODAS AS CARTAS DESSE DECK;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    std::vector<CardImage> getCardsImageByDeckIdSortedByDate(int deck_id);// OLHA O ID FORNECIDO E RETORNA UM VECTOR COM TODAS AS CARTAS DESSE DECK ORDENADAS PELA DATA;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    

    int createCardImage(CardImage& card);//USA A CARTA FORNECIDA PARA CRIAR UMA NOVA, O NOVO ID SERA COLOCADO NA CARTA FORNECIDA E RETORNA SE A OPERAÇÂO OCORREU;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    bool updateCardImage(CardImage& card);//USA A CARTA FORNECIDA PARA EDITAR UMA EXISTENTE, O ID DA CARTA FORNECIDA SERA O USADO PARA EDITAR A CARTA EQUIVALENTE E RETORNA SE A OPERAÇÂO OCORREU;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    bool deleteCardImage(int id);//USA O ID FORNECIDO PARA DELETAR UMA EXISTENTE E RETORNA SE A OPERAÇÂO OCORREU;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    
    bool deleteCardsImageByDeckId(int deck_id);//USA O ID DO DECK FORNECIDO PARA DELETAR TODOS OS CARDS COM ESSE deck_id ;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    

    //std::vector<Card> searchCardsByFront(const std::string& front);

};

#endif