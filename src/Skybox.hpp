#ifndef SKYBOX_HPP_INCLUDED
#define SKYBOX_HPP_INCLUDED

#include "OpenGL.hpp"
#include "Config.hpp"

class Skybox {
private:
	GLuint texture;

public:
	void load(const char* file);
	void draw(void);
};

#endif  // SKYBOX_HPP_INCLUDED
