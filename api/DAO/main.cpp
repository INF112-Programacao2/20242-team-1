//ARQUIVO TESTE!!!
//PARA RODAR CODIGO: 
//g++ main.cpp DatabaseConnection.cpp deckdao.cpp carddao.cpp ../card.cpp ../deck.cpp ../date.cpp sqlite3.dll 
// Para o linux: (necessário estar na pasta api)
// g++ deck.cpp ./DAO/deckdao.cpp ./DAO/DatabaseConnection.cpp ./DAO/main.cpp -o out -lsqlite3
#include "DatabaseConnection.h"
#include "deckdao.h"
#include "carddao.h"
#include "sqlite3.h"
#include "../card.h"
#include "../deck.h"
#include "../date.h"
#include "../media.h"
#include "../audio.h"
#include "../cardaudio.h"
#include "../image.h"
#include "../cardimage.h"

int main (){
    try{
        DatabaseConnection z("../dados.db");//mudar para "../dados.db" linux; mudar para "../../dados.db" windows
        DeckDAO y(z);
        CardDAO x(z); 
        
        /*Card a("7 + 3","10",1);
        Card b("2 + 1","3",1);
        Card c("7 - 2","5",1);*/

        //Card d("Hi","Hello",2);
        //Card e("He","Him",2);

        /*x.createCard(a);
        x.createCard(b);
        x.createCard(c);*/
        
       /* x.createCard(d);
        x.createCard(e);*/
        
        //x.createCard(f);

        //x.deleteCard(1);

        /*Card f("7+7","14",1);
        f.setId(2);
        x.updateCard(f);*/

        //x.deleteCardsByDeckId(2);

        //std::vector<Card> a = x.getAllCards();
       // Date data;
        //std::vector<Card> a = x.getCardsByDate(data,1);
        //std::vector<Card> a = x.getAllCardsSortedByDate();
        //std::vector<Card> a = x.getCardsByDeckId(1);
        //std::vector<Card> a = x.getCardsByDeckIdSortedByDate(1);

        /*for(Card card : a){
            std::cout << card.getFront() << " " << card.getBack() << " " << card.getDeckId() << " " << card.getId() << " " << card.getLastReview().getDateBystring() << std::endl; 
        }
       /*
        Audio a;
        a.setId(1);
        a.setName("test");
        a.setType("all");
        a.setDurationInSeconds(30);
        a.setTranscription("Nada");
        CardAudio cardaudio;
        cardaudio.setId(1);
        cardaudio.setAudio(a);
        std::cout << cardaudio.getAudio().getDurationInSeconds() << std::endl; 

        Image img;
        img.setCaption("Teste");
        img.setName("Teste");
        CardImage carImg;
        carImg.setImage(img);
        std::cout << carImg.getImage().getCaption() << std::endl; 
        */
    }catch (const std::exception& e){
        std::cerr << "Excecao capturada: " << e.what() << std::endl;
    }

    return 0;
}