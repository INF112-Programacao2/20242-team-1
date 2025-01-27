//ARQUIVO TESTE!!!
//PARA RODAR CODIGO: 
//g++ main.cpp DatabaseConnection.cpp deckdao.cpp carddao.cpp cardImageDAO.cpp imageDAO.cpp cardAudioDAO.cpp audioDAO.cpp ../card.cpp ../cardimage.cpp ../cardaudio.cpp ../deck.cpp ../date.cpp ../image.cpp ../audio.cpp ../media.cpp  sqlite3.dll
// Para o linux: (necessário estar na pasta api)
// g++ deck.cpp ./DAO/deckdao.cpp ./DAO/DatabaseConnection.cpp ./DAO/main.cpp -o out -lsqlite3
#include "carddao.h"
#include "cardImageDAO.h"
#include "cardAudioDAO.h"
#include "DatabaseConnection.h"
#include "deckdao.h"
#include "imageDAO.h"
#include "audioDAO.h"

#include "sqlite3.h"

#include "../deck.h"

#include "../card.h"
#include "../cardaudio.h"
#include "../cardimage.h"

#include "../date.h"
#include "../audio.h"
#include "../image.h"
#include "../media.h"





int main (){
    try{
        DatabaseConnection db("../../dados.db");//mudar para "../dados.db" linux; mudar para "../../dados.db" windows
        CardAudioDAO CardAudioDAO(db);
        CardImageDAO CardImageDAO(db);
        
        Image img(10,10,"nome","legenda","path");
        CardImage cardd("front","back",1);
        cardd.setImage(img);
        CardImageDAO.createCardImage(cardd);

        //Audio au("Casa2","legenda2",10,"caminho2");
        //CardAudio cad("front2","back2",1);
        //cad.setAudio(au);
        //CardAudioDAO.createCardAudio(cad);

       // CardAudioDAO.deleteCardAudio(1);

    }catch (const std::exception& e){
        std::cerr << "Excecao capturada: " << e.what() << std::endl;
    }

    return 0;
}