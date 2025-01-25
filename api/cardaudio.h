#ifndef CARDAUDIO_H
#define CARDAUDIO_H

#include "audio.h"
#include "card.h"

class CardAudio : public Card{

    private:
        Audio audio; // Áudio do card

    public:
        CardAudio();
        CardAudio(int id, std::string name, std::string path);
        ~CardAudio() = default;

        // ======= Getters =======

        Audio getAudio() const;

        // ======= Setters =======

        void setAudio(const Audio& audio);

        // ======= Methods =======

        void showCard();
};
#endif // CARDAUDIO_H