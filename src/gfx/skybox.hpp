#ifndef SKYBOX_HPP_INCLUDED
#define SKYBOX_HPP_INCLUDED

#include "config.hpp"
#include <GL/glew.h>
#define ILUT_USE_OPENGL
#include "ilut_compat.hpp"
#include "types.hpp"
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

class Skybox {
private:
    GLuint texture;

public:
    Skybox() : texture(0) {}

    void load(const char* file) {
        texture = ilutGLLoadImage(const_cast<char*>(file));
        if (texture == 0)
            return;
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void draw(void) {
        static GLuint list = 0;
        static int last = GetElapsedTime();
        static double k = 0;

        if (list == 0) {
            list = glGenLists(1);
            glNewList(list, GL_COMPILE);

            glBindTexture(GL_TEXTURE_2D, texture);
            glEnable(GL_TEXTURE_2D);

            glMatrixMode(GL_MODELVIEW);
            glScalef(1500, 1000, 3000);

            // Top
            glBegin(GL_QUADS);
            glTexCoord2d(0.0, 0.0);
            glVertex3d(-1, 1, 1);
            glTexCoord2d(1.0, 0.0);
            glVertex3d(1, 1, 1);
            glTexCoord2d(1.0, 1.0);
            glVertex3d(1, 1, -1);
            glTexCoord2d(0.0, 1.0);
            glVertex3d(-1, 1, -1);
            glEnd();

            // Front
            glBegin(GL_QUADS);
            glTexCoord2d(0.0, 0.0);
            glVertex3d(-1, 1, -1);
            glTexCoord2d(1.0, 0.0);
            glVertex3d(1, 1, -1);
            glTexCoord2d(1.0, 1.0);
            glVertex3d(1, -1, -1);
            glTexCoord2d(0.0, 1.0);
            glVertex3d(-1, -1, -1);
            glEnd();

            // Back
            glBegin(GL_QUADS);
            glTexCoord2d(0.0, 0.0);
            glVertex3d(-1, -1, 1);
            glTexCoord2d(1.0, 0.0);
            glVertex3d(1, -1, 1);
            glTexCoord2d(1.0, 1.0);
            glVertex3d(1, 1, 1);
            glTexCoord2d(0.0, 1.0);
            glVertex3d(-1, 1, 1);
            glEnd();

            // Left
            glBegin(GL_QUADS);
            glTexCoord2d(0.0, 0.0);
            glVertex3d(-1, -1, 1);
            glTexCoord2d(1.0, 0.0);
            glVertex3d(-1, -1, -1);
            glTexCoord2d(1.0, 1.0);
            glVertex3d(-1, 1, -1);
            glTexCoord2d(0.0, 1.0);
            glVertex3d(-1, 1, 1);
            glEnd();

            // Right
            glBegin(GL_QUADS);
            glTexCoord2d(0.0, 0.0);
            glVertex3d(-1, 1, 1);
            glTexCoord2d(1.0, 0.0);
            glVertex3d(-1, 1, -1);
            glTexCoord2d(1.0, 1.0);
            glVertex3d(-1, -1, -1);
            glTexCoord2d(0.0, 1.0);
            glVertex3d(-1, -1, 1);
            glEnd();

            // Other side
            glBegin(GL_QUADS);
            glTexCoord2d(0.0, 0.0);
            glVertex3d(1, -1, 1);
            glTexCoord2d(1.0, 0.0);
            glVertex3d(1, -1, -1);
            glTexCoord2d(1.0, 1.0);
            glVertex3d(1, 1, -1);
            glTexCoord2d(0.0, 1.0);
            glVertex3d(1, 1, 1);
            glEnd();

            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);
            glEndList();
        } else {
            if (GetConfigurationInt(AnimateSkybox)) {
                if (last + 10 <= GetElapsedTime()) {
                    k += 0.001;
                    last = GetElapsedTime();
                }

                glMatrixMode(GL_TEXTURE);
                glLoadIdentity();
                glTranslated(k, 0.0, 0.0);
            }

            glMatrixMode(GL_MODELVIEW);
            glCallList(list);
        }
    }
};

#endif // SKYBOX_HPP_INCLUDED
