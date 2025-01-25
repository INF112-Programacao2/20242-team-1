#ifndef AUDIO_H
#define AUDIO_H

#include "media.h"

class Audio : Media {
    private:
        float durationInSeconds;        // Duração do áudio em segundos
        std::string transcription;      // Transcrição do áudio
    public:
        Audio();
        Audio(int id, std::string name, std::string path);
        ~Audio() = default;

        // ======= Getters =======

        float getDurationInSeconds() const;
        std::string getTranscription() const;

        // ======= Setters =======

        void setDurationInSeconds(float durationInSeconds);
        void setTranscription(const std::string& transcription);

        // ======= Methods =======

        void updateAudio(int id, const std::string& name, const std::string& path);

};

#endif