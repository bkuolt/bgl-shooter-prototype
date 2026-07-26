#ifndef KEY_HPP_INCLUDED
#define KEY_HPP_INCLUDED

#include <GL/glew.h>
#include <GL/freeglut.h>

enum Key {
    Key_Esc = 27,
    Key_Up = 256 + GLUT_KEY_UP,
    Key_Down = 256 + GLUT_KEY_DOWN,
    Key_Left = 256 + GLUT_KEY_LEFT,
    Key_Right = 256 + GLUT_KEY_RIGHT
};

#endif // KEY_HPP_INCLUDED
