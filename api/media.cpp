#include "media.h"

/*
* @brief Construtor da classe Media, que inicia uma mídia nula
*/
Media::Media(){
    this->id = -1;
    this->name = "";
    this->path = "";
    this->type = "";
    this->file_size = 0;
}

/*
* @brief Construtor da classe Media, que inicia uma mídia com nome, caminho e tamanho do arquivo
* @param std::string Nome da mídia
* @param std::string Caminho da mídia
* @return void
*/
Media::Media(int id, std::string name, std::string path){
    this->id = id;
    this->name = name;
    this->path = path;

    /*
    * @TODO: Atualizar a função para setar corretamente o tamanho do arquivo e o tipo da mídia
    */

}
