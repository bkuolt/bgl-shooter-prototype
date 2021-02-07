#define _WIN32_WINNT  0x0501
#include "Windows.h"
#include "GLee.h"
#include "BSP.h"
#include <GL/glut.h>
#include <string>
#include <stdlib.h>
#include <ctype.h>
#include "GL/GL.h"
#include "BoundingBox.h"
#include "MD2.h"
#include "AL.h"
#include "ALUT.h"
#include "Sound.h"
#include "Config.h"
#include "Wincon.h"

Weapon weapon;
Camera camera(Vector(0,0,0),Vector(0,0,-1),ViewingFrustum(1,1,0.5,3500.0));

/*
===========================================================================
Haupt-Renderfunktion
===========================================================================*/
static void display(void) {
    static int fps = 0;
    static int last_fps = 0;
    static int time = GetElapsedTime();

    /*
    =============================================================
    Rendert BSP
    =============================================================*/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera.set();
    CD::RenderVisibleClusters();

    if(GetConfigurationInt(AnimateWater)) RenderWater();
    if(GetConfigurationInt(DrawSkybox))   skybox.draw();

    /*
    =============================================================
    Zeichner Waffe
    =============================================================*/
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(-5, 0, 3.7);
    glRotatef(-90,1, 0, 0);
    glRotatef(90, 0, 0,1);
    weapon.animate();

    /*
    =============================================================
    Teichnet Fadenkreuz
    =============================================================*/
    static const float l = 0.05f;
    glLineWidth(1);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D (-1.0, 1.0, -1.0, 1.0);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();

    glBegin(GL_LINES);
        glColor4f(0.5f,0.5f,0.5f,1.0f);
        glVertex2f(-l / 2,0.0f);
        glVertex2f( l / 2,0.0f);
        glVertex2f(0.0f, l / 2.0f);
        glVertex2f(0.0f,-l / 2.0f);
    glEnd();

    /*
    =============================================================
    Zeichnet Texteinblendungen
    =============================================================*/
    // Holt Informationen
    static const char* text_bgl = "BGL BSP Rendering Tech Demo!";
    const char* text_cd = CD::GetCollisionDetetctionString();
    static char text_tree[100];
    sprintf(text_tree,"FPS: %3i, %s",last_fps,CD::GetVisibiltyString());

    // BGL Info
    glColor3f((GetElapsedTime() - time) / 1000.0,0.0f,0.0f);
    glWindowPos2i(0,10);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18,text_bgl);

    // FPS und Bauminfo
    glColor3f(1,1,1);
    glWindowPos2i(0,glutGet(GLUT_WINDOW_HEIGHT)-18);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18,text_tree);

    //Kollisionserkennunginfo
    glWindowPos2i(0,glutGet(GLUT_WINDOW_HEIGHT)-40);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18,text_cd);

    /*
    =============================================================
    Misst FPS
    =============================================================*/
    if(GetElapsedTime() >= time + 1000){
        time = GetElapsedTime();
        last_fps = fps;
        fps = 0;
    }
    else
        ++fps;

    glutSwapBuffers();

}
void CameraCallback(int x,int y);
void CameraCallback(int x,int y,int button,int state);

/*
===========================================================================
GLUT Callbacks
===========================================================================*/
static void key(unsigned char key, int x, int y)
{
    GLUTCameraCallback(key,true);
    CameraCallback(x,y);
    glutPostRedisplay();
}

static void special(int key, int x, int y)
{
    GLUTCameraCallback(key,false);
    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

static void resize(int width, int height)
{
    display();
}

/*
===========================================================================
Infotext
===========================================================================*/
static HANDLE hStdOut;
static void PrintInfo(void)
{
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTitle("BGL Rendering Tech Demo!");
    SetConsoleTextAttribute(hStdOut,FOREGROUND_RED | FOREGROUND_INTENSITY);
    printf("=========================================================\n");
    printf("=         BGL BSP v38 Rendering (Prototype)             =\n");
    printf("=     This demo does not represent the final quality!   =\n");
    printf("=========================================================\n");
    printf("= OpenGL: %s\n",glGetString(GL_VERSION));
    printf("=    BGL: %s, %s [German]\n",__DATE__,__TIME__);
    printf("=========================================================\n");
    SetConsoleTextAttribute(hStdOut,FOREGROUND_BLUE| FOREGROUND_INTENSITY);
}

/*
===========================================================================
Main
===========================================================================*/

static void Init(void) {
    LoadConfiguration();

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH);

    const auto width  = GetConfigurationInt(ResolutionX);
    const auto = GetConfigurationInt(ResolutionY);

    if(GetConfigurationInt(Windowed)) {
        glutInitWindowSize(width,height);
        glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH)  / 2 - width  / 2,
                               glutGet(GLUT_SCREEN_HEIGHT) / 2 - height / 2);
        glutCreateWindow("BGL BSP Rendering Tech Demo");
    }
    else {
        char str[100];
        sprintf(str,"%ix%i:32",width,height);
        glutGameModeString(str);
        glutEnterGameMode();
    }

    // (3) Initialisiert Rendercallbacks
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    PrintInfo();

    /*
    =============================================================
    (3) OpenGL Inititialisierung
    =============================================================*/
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    /*
    =============================================================
    (4) Initialisiert Steuerung
    =============================================================*/
    glutSetCursor(GLUT_CURSOR_NONE);
    glutPassiveMotionFunc(CameraCallback);
    glutMotionFunc(CameraCallback);
    glutMouseFunc(CameraCallback);
    glutKeyboardFunc(key);
    glutSpecialFunc(special);

    /*
    =============================================================
    (5) L�dt Daten
    =============================================================*/

    // (1) L�dt Musikdateien
    if(GetConfigurationInt(PlayAudio)) {
        printf("Laedt Musikdateien...\n");

        alutInit(&argc, argv);
          gun.load(GetConfigurationString(DataPath) + "sound/weapon.wav");
        music.load(GetConfigurationString(DataPath) + "sound/music.wav");
        music.play(true);
        music.setVolume(0.25);
    }

    // (2) L�dt Waffenmodel
    printf("Laedt Waffenmodel...\n");
    weapon.load(GetConfigurationString(DataPath) + "weapon.md2");
    weapon.putaway();

    // (3) L�dt BSP
    SetConsoleTextAttribute(hStdOut,FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    LoadBSP((GetConfigurationString(DataPath) + "maps\\" + GetConfigurationString(Level)).c_str());

    /*
    =============================================================
    (6) Positioniert Spieler
    =============================================================*/
    printf("\tPositioniert Spieler... (letzer Schritt)\n");

    camera.translate(Vector(GetConfigurationFloatv(Position)[X],
                            GetConfigurationFloatv(Position)[Y],
                            GetConfigurationFloatv(Position)[Z]));
    camera.rotate(X,GetConfigurationFloatv(Rotation)[X]);
    camera.rotate(Y,GetConfigurationFloatv(Rotation)[Y]);


}


int main(int argc, char *argv[]) {
    Init();
    glutMainLoop();
    return 0;
}

/*
Todo:
    - Frustumcode korrigieren
    - Geschwindkeitsvektor
    - (Rotationssystem)
*/
