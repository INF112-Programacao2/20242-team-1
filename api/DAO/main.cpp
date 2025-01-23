//ARQUIVO TESTE!!!
//PARA RODAR CODIGO:
//g++ main.cpp DatabaseConnection.cpp deckdao.cpp ../card.cpp ../deck.cpp sqlite3.dll 

#include "DatabaseConnection.h"
#include "deckdao.h"
#include "sqlite3.h"
#include "../card.h"
#include "../deck.h"

int main (){
    try{
    DatabaseConnection a;
    DeckDAO b(a);
    Deck c("muitoo fodaa","Queee legaaalll");
    Deck d("oitenta","quarenta");
    c.setId(2);
    //b.createDeck(c);
    //b.createDeck(d);
    //b.deleteDeck(3);
    //b.updateDeck(c);
    Deck e = b.getDeckById(2);
    b.createDeck(e);
    }catch (const std::exception& e){
        std::cerr << "Excecao capturada: " << e.what() << std::endl;
    }

    return 0;
}