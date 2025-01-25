//ARQUIVO TESTE!!!
//PARA RODAR CODIGO: 
//g++ main.cpp DatabaseConnection.cpp deckdao.cpp ../card.cpp ../deck.cpp sqlite3.dll 
// Para o linux: (necessário estar na pasta api)
// g++ deck.cpp ./DAO/deckdao.cpp ./DAO/DatabaseConnection.cpp ./DAO/main.cpp -o out -lsqlite3
#include "DatabaseConnection.h"
#include "deckdao.h"
#include "sqlite3.h"
#include "../card.h"
#include "../deck.h"

int main (){
    try{
    DatabaseConnection a("../dados.db");
    DeckDAO b(a);
    std::array<Deck, 50> e= b.getAllDecks();
    for (int i = 0; i <= 3; ++i) {
        std::cout << e[i].getTitle()<<"\n" ;
    }
    }catch (const std::exception& e){
        std::cerr << "Excecao capturada: " << e.what() << std::endl;
    }

    return 0;
}