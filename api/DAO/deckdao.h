#ifndef DECKDAO_H
#define DECKDAO_H

#include "../deck.h"
#include "DatabaseConnection.h"
#include "sqlite3.h"

#include <iostream>
#include <vector>

//FAZER: remover  levelCollectio da tabela

class DeckDAO{
private:
    DatabaseConnection& db;

    bool deckExists(int id);
    int countDecks();

public:
    DeckDAO(DatabaseConnection& database);
    ~DeckDAO();

    int getDeckID(Deck& deck); //RETORNA O ID DO DECK DESEJADO, NO DECK ENVIADO DEVERA SER COLOCADO SOMENTE "TITLE E SUBJECT"; SE OCORRER ERRO IRA LANCAR UM THROW std::runtime_error()
    Deck getDeckById(int id);//RETORNA UM DECK COM O ID INFORMADO; SE OCORRER ERRO IRA LANCAR UM THROW std::runtime_error()
    //std::array<Deck,50> getAllDecks();//AINDA NAO FEITO
    
    // FUNCOES BOOL QUE RETORNARAO TRUE SE TIVEREM RODADO CORRETAMENTE
    bool createDeck(Deck& deck); //SE OCORRER ERRO IRA LANCAR UM THROW std::runtime_error()
    bool deleteDeck(int id);//SE OCORRER ERRO IRA LANCAR UM THROW std::runtime_error()
    bool updateDeck(const Deck& deck);//SE OCORRER ERRO IRA LANCAR UM THROW std::runtime_error()

    //ADICIONAR QUANDO CRIAR CLASSE CARD, AINDA NAO FEITO
    /*
    bool addCardToDeck(int deck_id, int card_id);
    bool deleteCardFromDeck(int deck_id, int card_id);
    std::array<Card,50> getCardsByDeckId(int deck_id);*/

    
};

#endif