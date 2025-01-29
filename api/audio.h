#ifndef AUDIO_H
#define AUDIO_H

#include "media.h"

class Audio : public Media {
    private:
        float durationInSeconds;        // Duração do áudio em segundos
        std::string transcription;      // Transcrição do áudio
    public:
        Audio();
        Audio(std::string name,std::string path,float durationInSeconds,std::string transcription);
        ~Audio() = default;

        // ======= Getters =======

        float getDurationInSeconds();
        std::string getTranscription();

        // ======= Setters =======

        void setDurationInSeconds(float durationInSeconds);
        void setTranscription(const std::string& transcription);

        // ======= Methods =======

        void updateAudio(int id, const std::string& name, const std::string& path);

};

#endif