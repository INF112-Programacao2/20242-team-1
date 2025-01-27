#ifndef CARDAUDIODAO_H
#define CARDAUDIODAO_H

#include "../card.h"
#include "DatabaseConnection.h"
#include "deckdao.h"
#include "../date.h"
#include "../cardaudio.h"
#include "../audio.h"
#include "audioDAO.h"

#include <algorithm>

class CardAudioDAO{
private:
    DatabaseConnection &db;

    void SortDate(std::vector<CardAudio>& cards); //ORGANIZA UM VECTOR DE CARDS PELA DATA 

public:

    CardAudioDAO(DatabaseConnection& database);  //CRIA A CLASSE E INICIA O DATABASE

    bool cardAudioExists(int id);                //BOOL QUE CHECA SE O ID DA CARTA ESCOLHIDA EXISTE; SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    int countCardsAudio();                       //CONTA QUANTAS CARTAS TEM EM TODO O DATABASE; SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    int countCardsAudioByDeck(int deck_id);      //CONTA QUANTAS CARTAS TEM EM UM DECK ESPECIFICO; ; SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error

    int getCardAudioIdByCardAudio(CardAudio& card);         //OLHA O FRONT E BACK DE UMA CARTA E RETORNA O ID DELA; SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error; SE NAO EXISTIR A CARTA IRA LANCAR std::invalid_argument
    int getAudioIdByCardAudioId(int id);
    CardAudio getCardAudioById(int id);               //OLHA O ID FORNECIDO E RETORNA UM CARD;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error; SE NAO EXISTIR O ID IRA LANCAR std::invalid_argument
    CardAudio getCardAudioByDate(Date date);          //OLHA A DATA FORNECIDA E RETORNA UM CARD;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error; SE NAO EXISTIR A DATA IRA LANCAR std::invalid_argument
    Date getDateByCardAudioId(int card_id);//OLHA O ID DA CARTA E RETORNA O lastReview;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error; SE NAO EXISTIR O ID IRA LANCAR std::invalid_argument
    Audio getAudioByCardAudioId(int card_id);
    CardAudio getCardAudioByAudio(Audio Audio);

    std::vector<CardAudio> getAllCardsAudio(); //RETORNA UM VECTOR COM TODAS AS CARTAS NOS DADOS;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    std::vector<CardAudio> getAllCardsAudioSortedByDate();
    std::vector<CardAudio> getCardsAudioByDeckId(int deck_id); // OLHA O ID FORNECIDO E RETORNA UM VECTOR COM TODAS AS CARTAS DESSE DECK;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    std::vector<CardAudio> getCardsAudioByDeckIdSortedByDate(int deck_id);// OLHA O ID FORNECIDO E RETORNA UM VECTOR COM TODAS AS CARTAS DESSE DECK ORDENADAS PELA DATA;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    

    bool createCardAudio(CardAudio& card);//USA A CARTA FORNECIDA PARA CRIAR UMA NOVA, O NOVO ID SERA COLOCADO NA CARTA FORNECIDA E RETORNA SE A OPERAÇÂO OCORREU;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    bool updateCardAudio(CardAudio& card);//USA A CARTA FORNECIDA PARA EDITAR UMA EXISTENTE, O ID DA CARTA FORNECIDA SERA O USADO PARA EDITAR A CARTA EQUIVALENTE E RETORNA SE A OPERAÇÂO OCORREU;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    bool deleteCardAudio(int id);//USA O ID FORNECIDO PARA DELETAR UMA EXISTENTE E RETORNA SE A OPERAÇÂO OCORREU;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    
    bool deleteCardsAudioByDeckId(int deck_id);//USA O ID DO DECK FORNECIDO PARA DELETAR TODOS OS CARDS COM ESSE deck_id ;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    

    //std::vector<Card> searchCardsByFront(const std::string& front);

};

#endif