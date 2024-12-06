
#include "OpenGL.hpp"
#include <gl/glut.h>

#include "Config.hpp"
#undef CreateWindow  // TODO
#undef UNICODE
#define _WIN32;
#define _WIN32_WINNT  0x0501#include <gl/glut.h>

#include <string>
#include <stdlib.h>
#include <ctype.h>

#include "BSP.hpp"
#include "Camera.hpp"
#include "Frustum.hpp"
#include "BoundingBox.hpp"
#include "MD2.hpp"
#include "Sound.hpp"
#include "Config.hpp"

static Weapon weapon;
static Camera camera(Vector(0, 0, 0), Vector(0, 0, -1), ViewingFrustum(1, 1, 0.5, 3500.0));



/**
 * @brief Haupt-Renderfunktion
 */
static void display(void) {
	static int fps = 0;
	static int last_fps = 0;
	static int time = GetElapsedTime();

	// Rendert BSP
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera.set();
	CD::RenderVisibleClusters();

	if (GetConfigurationInt(AnimateWater)) {
		RenderWater();
	}
	if (GetConfigurationInt(DrawSkybox)) {
		skybox.draw();
	}

	// Zeichnet Waffe
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-5, 0, 3.7);
	glRotatef(-90, 1, 0, 0);
	glRotatef(90, 0, 0, 1);
	weapon.animate();

	// Zeichnet Fadenkreuz
	static const float l = 0.05f;
	glLineWidth(1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_LINES);
	glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
	glVertex2f(-l / 2, 0.0f);
	glVertex2f(l / 2, 0.0f);
	glVertex2f(0.0f, l / 2.0f);
	glVertex2f(0.0f, -l / 2.0f);
	glEnd();

	// Zeichnet Texteinblendungen:
	// Holt Informationen
	static const char* text_bgl = "BGL BSP Rendering Tech Demo!";
	const char* text_cd = CD::GetCollisionDetetctionString();
	static char text_tree[100];
	sprintf(text_tree, "FPS: %3i, %s", last_fps, CD::GetVisibiltyString());

	// BGL Info
	glColor3f((GetElapsedTime() - time) / 1000.0, 0.0f, 0.0f);
	glWindowPos2i(0, 10);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, text_bgl);

	// FPS und Bauminfo
	glColor3f(1.0f, 1.0f, 1.0f);
	glWindowPos2i(0, glutGet(GLUT_WINDOW_HEIGHT) - 18);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, text_tree);

	// Kollisionserkennunginfo
	glWindowPos2i(0, glutGet(GLUT_WINDOW_HEIGHT) - 40);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, text_cd);

	// Misst FPS
	if (GetElapsedTime() >= time + 1000) {
		time = GetElapsedTime();
		last_fps = fps;
		fps = 0;
	}
	else {
		++fps;
	}

	glutSwapBuffers();
}




void CameraCallback(int x, int y);
void CameraCallback(int x, int y, int button, int state);


/**
 * @brief Konvertiert GLUT Keycodes und reicht sie an den eigentlichen Callback
 */
void GLUTCameraCallback(int key, bool ascii) {
	CameraCallback((ascii) ? toupper(key) : key + 256);
}
/*
===========================================================================
GLUT Callbacks
===========================================================================*/
static void key(unsigned char key, int x, int y) {
	GLUTCameraCallback(key, true);
	CameraCallback(x, y);
	glutPostRedisplay();
}

static void special(int key, int x, int y) {
	GLUTCameraCallback(key, false);
	glutPostRedisplay();
}

static void idle(void) {
	glutPostRedisplay();
}

static void resize(int width, int height) {
	display();
}




int CreateWindow(void (*display)(void)) {

	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH);

	const auto width = GetConfigurationInt(ResolutionX);
	const auto height = GetConfigurationInt(ResolutionY);


	if (GetConfigurationInt(Windowed)) {
		glutInitWindowSize(width, height);
		glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH) / 2 - width / 2,
			glutGet(GLUT_SCREEN_HEIGHT) / 2 - height / 2);
		glutCreateWindow("BGL BSP Rendering Tech Demo");
	}
	else {
		char str[100];
		sprintf(str, "%ix%i:32", width, height);
		glutGameModeString(str);
		glutEnterGameMode();
	}

	// (3) Initialisiert Rendercallbacks
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	PrintInfo();

	// (3) OpenGL Inititialisierung
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// (4) Initialisiert Steuerung
	glutSetCursor(GLUT_CURSOR_NONE);
	glutPassiveMotionFunc(CameraCallback);
	glutMotionFunc(CameraCallback);
	glutMouseFunc(CameraCallback);
	glutKeyboardFunc(key);
	glutSpecialFunc(special);

	return 0;  // TODO
}

/**
* @brief Infotext
*/
static void PrintInfo(void) {
	auto hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTitle("BGL Rendering Tech Demo!");
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("=========================================================\n");
	printf("=         BGL BSP v38 Rendering (Prototype)             =\n");
	printf("=     This demo does not represent the final quality!   =\n");
	printf("=========================================================\n");
	printf("= OpenGL: %s\n", glGetString(GL_VERSION));
	printf("=    BGL: %s, %s [German]\n", __DATE__, __TIME__);
	printf("=========================================================\n");

	SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}


