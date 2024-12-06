#ifndef SOUND_HPP_INCLUDED
#define SOUND_HPP_INCLUDED

#include <string>

class Sound {
public:
	static void Init(int argc, char** argv);

	~Sound();
	void load(const std::string& file);
	void play(bool repeat = false);
	void setVolume(float k);
	void stop(void);
	void setSpeed(float k);

private:
	unsigned int source;

};

#endif  // SOUND_HPP_INCLUDED
