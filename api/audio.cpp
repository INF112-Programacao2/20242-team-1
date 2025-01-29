#include "audio.h"
Audio::Audio() {};
Audio::Audio(std::string name,std::string path,float durationInSeconds,std::string transcription): Media(name,path)
{
    this->durationInSeconds = durationInSeconds;
    this->transcription = transcription;
};

// ======= Getters =======

float Audio::getDurationInSeconds()
{
    return this->durationInSeconds;
};
std::string Audio::getTranscription()
{
    return this->transcription;
};

// ======= Setters =======

void Audio::setDurationInSeconds(float durationInSeconds)
{
    this->durationInSeconds = durationInSeconds;
};
void Audio::setTranscription(const std::string &transcription)
{
    this->transcription = transcription;
};