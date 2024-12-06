#include "Sound.hpp"
#include "Config.h"

#include <al/al.h>
#include <al/alut.h>

void Sound::Init(int argc, char** argv) {
	alutInit(&argc, argv);
}

Sound::~Sound() {
	alDeleteSources(1, &source);
}

void Sound::load(const std::string& file) {
	if (GetConfigurationInt(PlayAudio)) {
		alGenSources(1, &source);
		alSourcei(source, AL_BUFFER, alutCreateBufferFromFile(file.c_str()));
	}
}

void Sound::play(bool repeat = false) {
	if (GetConfigurationInt(PlayAudio)) {
		alSourcei(source, AL_LOOPING, repeat);
		alSourcePlay(source);
	}
}

void Sound::setVolume(float k) {
	if (GetConfigurationInt(PlayAudio)) {
		alSourcei(source, AL_GAIN, k);
	}
}

void Sound::stop(void) {
	if (GetConfigurationInt(PlayAudio)) {
		alSourceStop(source);
	}
}

void Sound::setSpeed(float k) {
	if (GetConfigurationInt(PlayAudio)) {
		alSourcef(source, AL_PITCH, k);
	}
}