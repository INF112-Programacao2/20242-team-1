#include "audio.h"
Audio::Audio() {};
Audio::Audio(float durationInSeconds, std::string transcription)
{
    this->durationInSeconds = durationInSeconds;
    this->transcription = transcription;
};

// ======= Getters =======

float Audio::getDurationInSeconds() const
{
    return this->durationInSeconds;
};
std::string Audio::getTranscription() const
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