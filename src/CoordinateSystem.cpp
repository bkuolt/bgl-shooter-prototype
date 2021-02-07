#include "Windows.h"
#include "GLee.h"
#include <cstdio>
#include "GLUT.h"
#include "CoordinateSystem.h"

#ifdef __DEBUG__
/*
===================================================================
Zeichnet Koordinatensystem ein
===================================================================*/
void CoordinateSystem::draw(float unit,int length,int height) const
{
	float matrix[16];

    // Fehlerüberprüfung
    if(length == 0) return;
    length = abs(length);
    height = abs(height);

    glPushAttrib(GL_LINE_BIT | GL_CURRENT_BIT);
    glPushMatrix();
		// positioniert und richtet Koordinatensystem im 3D Raum aus
		// x-Achse
		matrix[0] = axes[X][X];
		matrix[1] = axes[X][Y];
		matrix[2] = axes[X][Z];
		matrix[3] = 0.0f;
		// y-Achse
		matrix[4] = axes[Y][X];
		matrix[5] = axes[Y][Y];
		matrix[6] = axes[Y][Z];
		matrix[7] = 0.0f;
		// z-Achse
		matrix[8] = axes[Z][X];
		matrix[9] = axes[Z][Y];
		matrix[10] =axes[Z][Z];
		matrix[11] = 0.0f;
		// Verschiebung
		matrix[12] = 0.0f;
		matrix[13] = 0.0f;
		matrix[14] = 0.0f;
		matrix[15] = 1.0f;

        glScalef(unit,unit,unit);
		glTranslatef(origin[X],origin[Y],origin[Z]);
        glMultTransposeMatrixf(matrix);

        // Gitternetz
        glEnable(GL_LINE_STIPPLE);
        glLineWidth(1.0);
        glLineStipple(unit,0xAAAA);

        glBegin(GL_LINES);
            glColor3f(0.0f,0.0f,0.0f);
            for(int i = -length;i <= length;(i == -1) ? i+= 2 : ++i){
                // Parallele zur x-Achse
                glVertex3i(-length,0,i);
                glVertex3i( length,0,i);
                // Parallele zur z-Achse
                glVertex3i(i,0,-length);
                glVertex3i(i,0, length);
            }
        glEnd();
        glDisable(GL_LINE_STIPPLE);

        // Koordinatensystem
        glLineWidth(2.0);
        for(int axis = 0;axis < 3;++axis)
        {
            glPushMatrix();
                // Koordinatenachsen
                glPushMatrix();
                    glScalef(length,1.0f,length);
                    glBegin(GL_LINES);
                        switch(axis){
                            case X:
                                glColor3f(1.0f,0.0f,0.0f);
                                glVertex3f(-1.0f,0.0f,0.0f);
                                glVertex3f( 1.0f,0.0f,0.0f);
                                break;
                            case Y:
                                glColor3f(0.0f,1.0f,0.0f);
                                glVertex3f(0.0f,-height,0.0f);
                                glVertex3f(0.0f, height,0.0f);
                                break;
                            case Z:
                                glColor3f(0.0f,0.0f,1.0f);
                                glVertex3f(0.0f,0.0f,-1.0f);
                                glVertex3f(0.0f,0.0f, 1.0f);
                                break;
                        }
                    glEnd();
                glPopMatrix();

            // Pfeilspitzen auf Koordinatenachsen
            switch(axis)
            {
                case X:
                    glTranslatef(length,0.0f,0.0f);
                    glRotatef(-90.0f,0.0f,0.0f,1.0f);
                    break;
                case Y:
                    glTranslatef(0.0,height,0.0f);
                    break;
                case Z:
                    glTranslatef(0.0f,0.0f,length);
                    glRotatef(-90.0f,0.0f,1.0f,0.0f);
                    glRotatef(-90.0f,0.0f,0.0f,1.0f);
                    break;
            }
                glPushMatrix();
                    glRotatef(-90,1,0,0);
                    glutSolidCone(0.5,1,100,100);
                glPopMatrix();
            glPopMatrix();
        }

        //Achsenbeschrifzung
        glColor3f(1.0f,0.0f,0.0f);
        glRasterPos3i(length + 1,0,0);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'X');

        glColor3f(0.0f,1.0f,0.0f);
        glRasterPos3i(0,length + 1,0);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'Y');

        glColor3f(0.0f,0.0f,1.0f);
        glRasterPos3i(0,0,length + 1);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'Z');

    glPopMatrix();
    glPopAttrib();
}
#endif

/*
======================================================================================================================================
======================================================================================================================================
======================================================================================================================================
======================================================================================================================================
======================================================================================================================================
======================================================================================================================================
======================================================================================================================================
======================================================================================================================================
======================================================================================================================================*/





























#include "CoordinateSystem.h"
#ifdef __DEBUG__
#include <GL/GL.h>
#endif

/*
===================================================================
Konstruktoren
===================================================================*/
CoordinateSystem::CoordinateSystem(void)
{
    axes[X] = Vector(1.0f,0.0f,0.0f);
    axes[Y] = Vector(0.0f,1.0f,0.0f);
    axes[Z] = Vector(0.0f,0.0f,1.0f);
}

CoordinateSystem::CoordinateSystem(const Vector &x,const Vector &y,const Vector &z)
{
   axes[X] = x;
   axes[Y] = y;
   axes[Z] = z;
}


void CoordinateSystem::normalize(void)
{
	axes[X].normalize();
	axes[Y].normalize();
	axes[Z].normalize();
}

void CoordinateSystem::rotate(Axis axis,float angle)
{
	// (1) rotieren, (andere Achsen mitrotieren)
	switch(axis)
	{
		case X:
			axes[Y].rotate(X,angle);
			axes[Z].rotate(X,angle);
			break;
		case Y:
			axes[X].rotate(Y,angle);
			axes[Z].rotate(Y,angle);
			break;
		case Z:
			axes[Y].rotate(Z,angle);
			axes[Z].rotate(Z,angle);
			break;
	}

	// (2) alle Vektoren normalisieren (Rundungsfehler eliminieren)
    normalize();
}

const Vector& CoordinateSystem::getAxis(Axis axis) const
{
	return axes[axis];
}

const Vector& CoordinateSystem::getOrigin(void) const
{
	return origin;
}

void CoordinateSystem::setOrigin(const Vector &v)
{
	origin = v;
}
