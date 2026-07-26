#ifndef SOUND_HPP_INCLUDED
#define SOUND_HPP_INCLUDED

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <cstdio>
#include <string>
#include <utility>

class Sound {
private:
    ALuint buffer{AL_NONE};
    ALuint source{AL_NONE};

public:
    Sound(void) = default;

    explicit Sound(const std::string& filename) { load(filename); }

    ~Sound(void) {
        clean();
    }

    Sound(const Sound&) = delete;
    Sound& operator=(const Sound&) = delete;

    Sound(Sound&& other) noexcept : buffer(other.buffer), source(other.source) {
        other.buffer = AL_NONE;
        other.source = AL_NONE;
    }

    Sound& operator=(Sound&& other) noexcept {
        if (this != &other) {
            clean();
            buffer = std::exchange(other.buffer, AL_NONE);
            source = std::exchange(other.source, AL_NONE);
        }
        return *this;
    }

    void clean(void) {
        if (source != AL_NONE) {
            alDeleteSources(1, &source);
            source = AL_NONE;
        }
        if (buffer != AL_NONE) {
            alDeleteBuffers(1, &buffer);
            buffer = AL_NONE;
        }
    }

    void load(const std::string& filename) {
        clean();
        alutInit(nullptr, nullptr);
        buffer = alutCreateBufferFromFile(filename.c_str());
        if (buffer != AL_NONE) {
            alGenSources(1, &source);
            alSourcei(source, AL_BUFFER, buffer);
        }
    }

    void play(bool loop = false) {
        if (source != AL_NONE) {
            alSourcei(source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
            alSourcePlay(source);
        }
    }

    void stop(void) {
        if (source != AL_NONE) {
            alSourceStop(source);
        }
    }

    void setVolume(float volume) {
        if (source != AL_NONE) {
            alSourcef(source, AL_GAIN, volume);
        }
    }

    void setSpeed(float speed) {
        if (source != AL_NONE) {
            alSourcef(source, AL_PITCH, speed);
        }
    }
};

#endif // SOUND_HPP_INCLUDED
