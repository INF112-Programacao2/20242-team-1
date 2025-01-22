#ifndef CARD_H
#define CARD_H

#include <string>
// #include <ctime>

class Card{
    private:
        int id;             // Identificador
        std::string front;  // Frente da carta
        std::string back;   // Verso da carta
        // int deck_id;        // Baralho ao qual a carta pertence
        // int levelTime_id;   // Nível de tempo ao qual a carta pertence
        //Data lastReview; // Última vez que a carta foi estudada
        
        // ----------------- //
        // Sugestão: usar a biblioteca <ctime> para manipulação de datas,
        // mas separado em outra classe - Data.h e Data.cpp
        // MAIOR ACOPLAMENTO ENTRE AS CLASSES
        // Info: https://www.cplusplus.com/reference/ctime/
        // ----------------- //

    public:
        Card();

        // Getters
        int getId() const;
}; // @TODO

#endif // CARD_H