#include "cardaudio.h"


       CardAudio::CardAudio(){};
       CardAudio::CardAudio(std::string front, std::string back, int deck_id): Card(front,back,deck_id){}


        // ======= Getters =======

        Audio& CardAudio::getAudio(){
            return this->audio;
        };

        int CardAudio::getAudioId(){
            return this->audio_id;
        }

        // ======= Setters =======

        void CardAudio::setAudio(const Audio& audio){
            this->audio =audio;
        };
        void CardAudio::setAudioId(int audio_id){
            this->audio_id = audio_id;
        }

        // ======= Methods =======

        void CardAudio::showCard(){

        };