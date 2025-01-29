#ifndef CARDAUDIO_H
#define CARDAUDIO_H

#include "audio.h"
#include "card.h"

class CardAudio : public Card{

    private:
        Audio audio; // Áudio do card
        int audio_id;

    public:
        CardAudio();
        CardAudio(std::string front, std::string back, int deck_id);
        ~CardAudio() = default;

        // ======= Getters =======

        Audio& getAudio();
        int getAudioId();

        // ======= Setters =======

        void setAudio(const Audio& audio);
        void setAudioId(int audio_id);

        // ======= Methods =======

        void showCard();
};
#endif // CARDAUDIO_H