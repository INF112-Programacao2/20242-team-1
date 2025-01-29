#ifndef AUDIODAO_H
#define AUDIODAO_H

#include "DatabaseConnection.h"
#include "../audio.h"

#include <algorithm>

class AudioDAO{
private:
    DatabaseConnection &db;

public:

    AudioDAO(DatabaseConnection& database);  //CRIA A CLASSE E INICIA O DATABASE

    bool AudioExists(int id);                //BOOL QUE CHECA SE O ID DA Audio ESCOLHIDA EXISTE; SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error

    Audio getAudioById(int id);               //OLHA O ID FORNECIDO E RETORNA UM CARD;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error; SE NAO EXISTIR O ID IRA LANCAR std::invalid_argument

    bool createAudio(Audio& Audio);//USA A Audio FORNECIDA PARA CRIAR UMA NOVA, O NOVO ID SERA COLOCADO NA Audio FORNECIDA E RETORNA SE A OPERAÇÂO OCORREU;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    bool updateAudio(Audio& Audio);//USA A Audio FORNECIDA PARA EDITAR UMA EXISTENTE, O ID DA Audio FORNECIDA SERA O USADO PARA EDITAR A Audio EQUIVALENTE E RETORNA SE A OPERAÇÂO OCORREU;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    bool deleteAudio(int id);//USA O ID FORNECIDO PARA DELETAR UMA EXISTENTE E RETORNA SE A OPERAÇÂO OCORREU;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error

    //std::vector<Card> searchCardsByFront(const std::string& front);

};



#endif