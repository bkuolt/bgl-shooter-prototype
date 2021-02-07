#include "BoundingBox.h"
#include "BSP.h"
#include "GLUT.h"
#include <cctype>

static Camera *current_camera = NULL;

/*
=================================================================================
=                                                                               =
=                                FPS Camera                                     =
=                                                                               =
=================================================================================*/

Camera::Camera(const Vector &position,const Vector &focus,const ViewingFrustum &frustum)
    : position(position), focus(focus), frustum(frustum), angle(0.0f)  // Angepasste Einstellungen
{
    current_camera = this;
    calculateBoundingSphere();
}

Camera::Camera(void)
    : position(0.0f,0.0f,0.0f), focus(0.0f,0.0f,-1.0f), angle(0.0f)  // OpenGL Standardeinstellungen
{
    current_camera = this;
    calculateBoundingSphere();
}

Camera::Camera(const ViewingFrustum &frustum)
    : position(0.0f,0.0f,0.0f), focus(0.0f,0.0f,-1.0f), frustum(frustum), angle(0.0f) {
    current_camera = this;
    calculateBoundingSphere();
}

/*
=================================================================================
Berechnet AABB der Kamera
=================================================================================*/
void Camera::calculateBoundingSphere(void) {
     sphere = BoundingSphere(position, frustum.near);
}

/*
=================================================================================
Positioniert Kamera im 3D Raum
=================================================================================*/
void Camera::set(void) const {
    Vector focus = getFocus();

	// Setzt Sichtfeld (Projektion)
	frustum.set();

	// Setzt Blickrichtung
    glMatrixMode(GL_TEXTURE);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(position[X], position[Y], position[Z],                                  // Position
			  position[X] + focus[X], position[Y] + focus[Y], position[Z] + focus[Z], // Fokus
			  0.0f, 1.0f, 0.0f);
}

/*
=================================================================================
Verschiebt Kamera
=================================================================================*/
void Camera::translate(const Vector &v) {
    // Überprüft,ob Kollision bei Verschiebung auftretten wwürderde
    if (!CD::WouldHaveWallCollision(v)) {
        position += v;
        sphere.translate(v);
        frustum.translate(v);
    }
}

/*
=================================================================================
Rotiert Kamera
=================================================================================*/
void Camera::rotate(Axis axis,float step) {
    static float x = 0.0f;

    if (axis == X) {
        // Überprüft,ob "Kopf" sich nicht mehr als 90° nach oben und unten bewegt
        if (x + step < 90.0f && x + step > -90.0f) x+=step; else return;
        focus.rotate(axis,step).normalize();
    }
    else if (axis == Y)
        angle+= step;

    frustum.rotate(position,axis,step);
}

Vector Camera::getFocus(void) const {
    return Vector(focus).rotate(Y,angle).normalize();
}

/*
=================================================================================
Bewegt Kamera nach links bzw.nach rechts
=================================================================================*/
void Camera::moveLeft(float step) {
    translate(CrossProduct(Vector(0.0f,1.0f,0.0f),getFocus()).normalize() * fabs(step));
}

void Camera::moveRight(float step) {
    translate(CrossProduct(Vector(0.0f,1.0f,0.0f),getFocus()).normalize() * -fabs(step));
}

/*
=================================================================================
Bewegt Kamera nach oben bzw. nach unten
=================================================================================*/
void Camera::moveUp(float step) {
    translate(Vector(0.0f, fabs(step), 0.0f));
}

void Camera::moveDown(float step) {
    translate(Vector(0.0f, -fabs(step), 0.0f));
}

/*
=================================================================================
Bewegt Kamera nach vorne bzw. nach hinten. Die y-Kompenente der Verschiebung ist
0,da sonst "Freelook"
=================================================================================*/
void Camera::moveForward(float step) {
    translate(Vector(getFocus()[X],0.0f,getFocus()[Z]).normalize() * fabs(step));
}

void Camera::moveBackward(float step) {
    translate(Vector(getFocus()[X],0.0f,getFocus()[Z]).normalize() * -fabs(step));
}

/*
=================================================================================
Rotiert Kamera nach oben bzw. nach unten
=================================================================================*/
void Camera::rotateUp(float step) {
    rotate(X, fabs(step));
}

void Camera::rotateDown(float step) {
    rotate(X, -fabs(step));
}

/*
=================================================================================
Rotiert Kamera nach links bzw. nach rechts
=================================================================================*/
void Camera::rotateLeft(float step) {
    rotate(Y, fabs(step));
}

void Camera::rotateRight(float step) {
    rotate(Y, -fabs(step));
}

/*
=================================================================================
Gibt Kameraposition zur�ck
=================================================================================*/
const Vector& Camera::getPosition(void) const {
    return position;  // K�nnte Probleme bei der AABB Kollisionserkennung geben!
}

Vector Camera::getVisiblePosition(void) const {
    //Vector offset(0,-2.5,0); // Offset sorgt daf�r,dass es zu keinen Clippingfehlern mit dem Bodem kommt
    return position + Vector(focus).normalize() * frustum.near; // K�nnte Probleme bei der AABB Kollisionserkennung geben!
}

#ifdef __DEBUG__
/*
*********************************************************************************
*                                                                               *
*                           FPS Camera Control                                  *
*                                                                               *
*********************************************************************************
* HINWEIS: F�r Testzwecke wird die Tastatur-Kamerasteurung hier implementiert!  *
*********************************************************************************/
// Vorw�rtsdeklarartionen
static void CameraCallback(int key);

// Tastendefinitionen
enum {
    K = 'K',
    F = 'F',
	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',
	Esc = 27,
	Plus  = '+',
	Minus = '-',
	Up    = 256 + GLUT_KEY_UP,
	Down  = 256 + GLUT_KEY_DOWN,
	Left  = 256 + GLUT_KEY_LEFT,
	Right = 256 + GLUT_KEY_RIGHT
};

static Camera &camera = *current_camera;
static const float move_step     = 9.0f;
static const float rotation_step = 5.0f;

/*
=================================================================================
Konvertiert GLUT Keycodes und reicht sie an den eigentlichen Callback
=================================================================================*/
void GLUTCameraCallback(int key,bool ascii) {
	CameraCallback((ascii) ? toupper(key) : key + 256);
}

/*
=================================================================================
=                   Eigentliche Tastatur-Kamerasteuerung                        =
=================================================================================*/
static void CameraCallback(int key) {
    float step = move_step;

	switch(key) {
	    // Beendet Programm
	    case Esc: exit(0); break;

	    // Waffen einstecken/rausholen
        case 'F': weapon.putaway(); break;
        case 'K': detect_collisions = !detect_collisions; break;

		// Rotiert Kamera
		case Left:  camera.rotateLeft(step);  break;
		case Right: camera.rotateRight(step); break;
		case Down:  camera.rotateDown(step);  break;
		case Up:    camera.rotateUp(step);    break;

		// Bewegt Kamera auf/ab
		case Plus:  camera.moveUp(step);   break;
		case Minus: camera.moveDown(step); break;

		// Bewegt Kamera nach links/recht/vorne/hinten
		case W: camera.moveForward(step);  break;
		case S: camera.moveBackward(step); break;
		case A: camera.moveLeft(step);     break;
		case D: camera.moveRight(step);    break;
	}
}

/*
=================================================================================
=                     Eigentliche Maus-Kamerasteuerung                          =
=================================================================================*/
void CameraCallback(int x,int y) {
    static Vector last;
	static const float step =  rotation_step;

    // Rotiert Kamera nach links und rechts
    if (x - last[X] < 0)      camera.rotateLeft(step);
    else if (x - last[X] > 0) camera.rotateRight(step);

    // Rotiert Kamera nach oben und unten
    if (y - last[Y] < 0)      camera.rotateUp(step);
    else if (y - last[Y] > 0) camera.rotateDown(step);

    // Speichert letzte Koordinaten
    last[X] = x;
    last[Y] = y;

    // Zentriert Masuzeiger
    if (x > glutGet(GLUT_WINDOW_WIDTH)  * 0.75f || x < glutGet(GLUT_WINDOW_WIDTH)  * 0.25f ||
        y > glutGet(GLUT_WINDOW_HEIGHT) * 0.75f || y < glutGet(GLUT_WINDOW_HEIGHT) * 0.25f)
       SetCursorPos(glutGet(GLUT_WINDOW_WIDTH)  / 2,glutGet(GLUT_WINDOW_HEIGHT) / 2);

    glutPostRedisplay();
}

/*
=================================================================
= GLUT v3.7.6 Patch (neue DLL und LIB, aber kein neuen Header!) =
= http://www.realmtech.net/opengl/glut.php                      =
=================================================================*/
//Mausrad
#ifndef GLUT_WHEEL_UP
    #define GLUT_WHEEL_UP   3
    #define GLUT_WHEEL_DOWN 4
#endif

void CameraCallback(int button,int state,int x,int y) {
    // Verarbeitet Mausrad Kamra hoch/runter
    if (button == GLUT_WHEEL_DOWN)
        camera.moveDown(move_step * 2);
    else if (button == GLUT_WHEEL_UP)
        camera.moveUp(move_step * 2);


    if(button == GLUT_LEFT_BUTTON)
        if(state == GLUT_DOWN)
            weapon.startShooting();
        else
            weapon.stopShooting();

    // verabrbeite Mausbewegung
    CameraCallback(x,y);
}
#endif
