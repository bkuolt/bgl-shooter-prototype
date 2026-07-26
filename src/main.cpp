#include "bsp.hpp"
#include "camera.hpp"
#include "config.hpp"
#include "md2.hpp"
#include "sound.hpp"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <string>

#include <spdlog/spdlog.h>

Camera camera(Vector(0, 0, 0), Vector(0, 0, -1), ViewingFrustum(1, 1, 0.5, 3500.0));

static bool is_initialized = false;

static void display(void) {
    if (!is_initialized) {
        return;
    }
    static int fps = 0;
    static int last_fps = 0;
    static int time = GetElapsedTime();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera.set();
    CD::RenderVisibleClusters();

    if (GetConfigurationInt(AnimateWater)) {
        RenderWater();
    }
    if (GetConfigurationInt(DrawSkybox)) {
        skybox.draw();
    }

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(-5, 0, 3.7);
    glRotatef(-90, 1, 0, 0);
    glRotatef(90, 0, 0, 1);
    weapon.animate();

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

    static const char* text_bgl = "BGL BSP Rendering Tech Demo!";
    const char* text_cd = CD::GetCollisionDetetctionString();
    static char text_tree[100];
    std::snprintf(text_tree, sizeof(text_tree), "FPS: %3i, %s", last_fps, CD::GetVisibiltyString());

    glColor3f((GetElapsedTime() - time) / 1000.0f, 0.0f, 0.0f);
    glWindowPos2i(0, 10);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, text_bgl);

    glColor3f(1.0f, 1.0f, 1.0f);
    glWindowPos2i(0, glutGet(GLUT_WINDOW_HEIGHT) - 18);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, text_tree);

    glWindowPos2i(0, glutGet(GLUT_WINDOW_HEIGHT) - 40);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, text_cd);

    if (GetElapsedTime() >= time + 1000) {
        time = GetElapsedTime();
        last_fps = fps;
        fps = 0;
    } else {
        ++fps;
    }

    glutSwapBuffers();
}

void CameraCallback(int x, int y);

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
    glViewport(0, 0, width, height);
    if (is_initialized) {
        display();
    }
}

static void PrintInfo(void) {
    spdlog::info("=========================================================");
    spdlog::info("=         BGL BSP v38 Rendering (Prototype)             =");
    spdlog::info("=     This demo does not represent the final quality!   =");
    spdlog::info("=========================================================");
    const char* gl_ver = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    spdlog::info("= OpenGL: {}", gl_ver ? gl_ver : "Unknown");
    spdlog::info("=    BGL: {}, {}", __DATE__, __TIME__);
    spdlog::info("=========================================================");
}

static void Init(int argc, char* argv[]) {
    LoadConfiguration();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH);

    const int width = (GetConfigurationInt(ResolutionX) > 0) ? GetConfigurationInt(ResolutionX) : 1920;
    const int height = (GetConfigurationInt(ResolutionY) > 0) ? GetConfigurationInt(ResolutionY) : 1080;

    glutInitWindowSize(width, height);
    if (GetConfigurationInt(Windowed)) {
        glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH) / 2 - width / 2,
                               glutGet(GLUT_SCREEN_HEIGHT) / 2 - height / 2);
        glutCreateWindow("BGL BSP Rendering Tech Demo");
    } else {
        glutCreateWindow("BGL BSP Rendering Tech Demo");
        glutFullScreen();
    }

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        spdlog::error("GLEW Error: {}", reinterpret_cast<const char*>(glewGetErrorString(err)));
    }

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    PrintInfo();

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glutSetCursor(GLUT_CURSOR_NONE);
    glutPassiveMotionFunc(CameraCallback);
    glutMotionFunc(CameraCallback);
    glutMouseFunc(CameraCallback);
    glutKeyboardFunc(key);
    glutSpecialFunc(special);

    if (GetConfigurationInt(PlayAudio)) {
        spdlog::info("Loading audio files...");
        alutInit(&argc, argv);
        gun.load(GetConfigurationString(DataPath) + "sound/weapon.wav");
        music.load(GetConfigurationString(DataPath) + "sound/music.wav");
        music.play(true);
        music.setVolume(0.25);
    }

    spdlog::info("Loading weapon model...");
    weapon.load(GetConfigurationString(DataPath) + "weapon.md2");
    weapon.putaway();

    LoadBSP((GetConfigurationString(DataPath) + "maps/" + GetConfigurationString(Level)).c_str());

    spdlog::info("Positioning player... (final step)");

    Vector spawn_pos(GetConfigurationFloatv(Position)[X], GetConfigurationFloatv(Position)[Y],
                     GetConfigurationFloatv(Position)[Z]);
    SwapAxis(spawn_pos);
    camera.setPosition(spawn_pos);
    camera.rotate(X, GetConfigurationFloatv(Rotation)[X]);
    camera.rotate(Y, GetConfigurationFloatv(Rotation)[Y]);

    is_initialized = true;
}

int main(int argc, char* argv[]) {
    Init(argc, argv);
    glutMainLoop();
    return 0;
}
