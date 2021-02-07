#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#include "AL.h"
#include "ALUT.h"
#include "Config.h"
#include <string>

class Sound
{
    private:
        ALuint source;
    public:
        void load(const std::string &file)
        {
            if(GetConfigurationInt(PlayAudio)){
                alGenSources(1,&source);
                alSourcei (source,AL_BUFFER,alutCreateBufferFromFile(file.c_str()));
            }
        }

        void play(bool repeat = false)
        {
            if(GetConfigurationInt(PlayAudio)){
                alSourcei (source,AL_LOOPING,repeat);
                alSourcePlay(source);
            }
        }

        void setVolume(float k)
        {
            if(GetConfigurationInt(PlayAudio))
                alSourcei (source,AL_GAIN,k);
        }
        void stop(void)
        {
            if(GetConfigurationInt(PlayAudio))
                alSourceStop(source);
        }

        void setSpeed(float k)
        {
            if(GetConfigurationInt(PlayAudio))
                alSourcef(source, AL_PITCH,k);
        }
};
#endif // SOUND_H_INCLUDED
