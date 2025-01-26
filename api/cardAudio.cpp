#include "cardaudio.h"


       CardAudio::CardAudio(){};


        // ======= Getters =======

        Audio CardAudio::getAudio() const{
            return this->audio;
        };

        // ======= Setters =======

        void CardAudio::setAudio(const Audio& audio){
            this->audio =audio;
        };

        // ======= Methods =======

        void CardAudio::showCard(){

        };