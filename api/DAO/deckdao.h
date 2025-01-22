#ifndef DECKDAO_H
#define DECKDAO_H

#include "api\deck.h"
#include "DatabaseConnection.h"

#include <iostream>
#include <vector>
#include <sqlite3.h>

//FAZER: remover  levelCollectio da tabela

class DeckDAO{
private:
    DatabaseConnection& db;

    bool deckExists(int id);
    int countDecks();

    bool beginTransaction();
    bool commitTransaction();
    bool rollbackTransaction();


public:
    DeckDAO(DatabaseConnection& database);
    ~DeckDAO();

    Deck getDeckById(int id);//RETORNA UM DECK COM O ID INFORMADO; SE OCORRER ERRO IRA LANCAR UM THROW std::runtime_error()
    int getDeckID(Deck& deck); //RETORNA O ID DO DECK DESEJADO, NO DECK ENVIADO DEVERA SER COLOCADO SOMENTE "TITLE E SUBJECT"; SE OCORRER ERRO IRA LANCAR UM THROW std::runtime_error()
    
    // FUNCOES BOOL QUE RETORNARAO TRUE SE TIVEREM RODADO CORRETAMENTE
    bool createDeck(Deck& deck); //SE OCORRER ERRO IRA LANCAR UM THROW std::runtime_error()
    bool deleteDeck(int id);//SE OCORRER ERRO IRA LANCAR UM THROW std::runtime_error()
    bool updateDeck(const Deck& deck);//SE OCORRER ERRO IRA LANCAR UM THROW std::runtime_error()

    bool addCardToDeck(int deck_id, int card_id);
    bool deleteCardFromDeck(int deck_id, int card_id);

    std::array<Deck,50> getAllDecks();
    std::array<Card,50> getCardsByDeckId(int deck_id);

    
};

#endif