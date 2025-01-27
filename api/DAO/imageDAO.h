#ifndef IMAGEDAO_H
#define IMAGEDAO_H

#include "DatabaseConnection.h"
#include "../image.h"

#include <algorithm>

class ImageDAO{
private:
    DatabaseConnection &db;

public:

    ImageDAO(DatabaseConnection& database);  //CRIA A CLASSE E INICIA O DATABASE

    bool ImageExists(int id);                //BOOL QUE CHECA SE O ID DA IMAGEM ESCOLHIDA EXISTE; SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error

    Image getImageById(int id);               //OLHA O ID FORNECIDO E RETORNA UM CARD;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error; SE NAO EXISTIR O ID IRA LANCAR std::invalid_argument

    bool createImage(Image& image);//USA A IMAGEM FORNECIDA PARA CRIAR UMA NOVA, O NOVO ID SERA COLOCADO NA IMAGEM FORNECIDA E RETORNA SE A OPERAÇÂO OCORREU;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    bool updateImage(Image& image);//USA A IMAGEM FORNECIDA PARA EDITAR UMA EXISTENTE, O ID DA IMAGEM FORNECIDA SERA O USADO PARA EDITAR A IMAGEM EQUIVALENTE E RETORNA SE A OPERAÇÂO OCORREU;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error
    bool deleteImage(int id);//USA O ID FORNECIDO PARA DELETAR UMA EXISTENTE E RETORNA SE A OPERAÇÂO OCORREU;SE OCORRER UM ERRO IRA LANCAR UM std::runtime_error

    //std::vector<Card> searchCardsByFront(const std::string& front);

};



#endif