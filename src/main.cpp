#include "OpenGL.hpp"

#include <gl/glut.h>

#include <string>
#include <stdlib.h>
#include <ctype.h>

#include "Camera.hpp"
#include "Frustum.hpp"
#include "MD2.hpp"
#include "Sound.hpp"
#include "Config.hpp"



namespace bgl {
#undef CreateWindow  // TODO
	int CreateWindow(void (*display)(void)));
};

static HANDLE hStdOut;
static Weapon weapon;
static Camera camera(Vector(0, 0, 0), Vector(0, 0, -1), ViewingFrustum(1, 1, 0.5, 3500.0));


int main(int argc, char* argv[]) {
	LoadConfiguration();

	int window = bgl::CreateWindow();

	/*
	=============================================================
	(5) Lädt Daten
	=============================================================*/

	// (1) Lädt Musikdateien
	if (GetConfigurationInt(PlayAudio)) {
		printf("Laedt Musikdateien...\n");

		Sound::Init(&argc, argv);
		gun.load(GetConfigurationString(DataPath) + "sound/weapon.wav");
		music.load(GetConfigurationString(DataPath) + "sound/music.wav");
		music.play(true);
		music.setVolume(0.25);
	}

	// (2) Lädt Waffenmodel
	printf("Laedt Waffenmodel...\n");
	weapon.load(GetConfigurationString(DataPath) + "weapon.md2");
	weapon.putaway();

	// (3) Lädt BSP
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	LoadBSP((GetConfigurationString(DataPath) + "maps\\" + GetConfigurationString(Level)).c_str());

	// (6) Positioniert Spieler
	printf("\tPositioniert Spieler... (letzer Schritt)\n");

	camera.translate(Vector(GetConfigurationFloatv(Position)[X],
		GetConfigurationFloatv(Position)[Y],
		GetConfigurationFloatv(Position)[Z]));
	camera.rotate(X, GetConfigurationFloatv(Rotation)[X]);
	camera.rotate(Y, GetConfigurationFloatv(Rotation)[Y]);

	glutMainLoop();
	return 0;
}
