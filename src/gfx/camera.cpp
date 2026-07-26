#include "camera.hpp"
#include "bsp.hpp"
#include "md2.hpp"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cctype>
#include <cstdlib>

static Camera* current_camera = nullptr;

extern weapon_t weapon;
extern bool detect_collisions;

/*
=================================================================================
FPS Camera
=================================================================================*/

Camera::Camera(const Vector& position, const Vector& focus, const ViewingFrustum& frustum)
    : position(position), focus(focus), frustum(frustum), angle(0.0f) {
    current_camera = this;
    calculateBoundingSphere();
}

Camera::Camera(void) : position(0.0f, 0.0f, 0.0f), focus(0.0f, 0.0f, -1.0f), angle(0.0f) {
    current_camera = this;
    calculateBoundingSphere();
}

Camera::Camera(const ViewingFrustum& frustum)
    : position(0.0f, 0.0f, 0.0f), focus(0.0f, 0.0f, -1.0f), frustum(frustum), angle(0.0f) {
    current_camera = this;
    calculateBoundingSphere();
}

/**
 * @brief Calculates bounding sphere of the camera
 */
void Camera::calculateBoundingSphere(void) {
    sphere = BoundingSphere(position, frustum.near_dist);
}

/**
 * @brief Positions camera in 3D space
 */
void Camera::set(void) const {
    Vector f = getFocus();

    frustum.set();

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(position[X], position[Y], position[Z], position[X] + f[X], position[Y] + f[Y], position[Z] + f[Z], 0.0f,
              1.0f, 0.0f);
}

/**
 * @brief Translates camera position
 */
void Camera::translate(const Vector& v) {
    if (!CD::WouldHaveWallCollision(v)) {
        position += v;
        sphere.translate(v);
        frustum.translate(v);
    }
}

void Camera::setPosition(const Vector& p) {
    Vector diff = p - position;
    position = p;
    sphere.translate(diff);
    frustum.translate(diff);
}

/**
 * @brief Rotates camera
 */
void Camera::rotate(Axis axis, float step) {
    static float x = 0.0f;

    if (axis == X) {
        if (x + step < 90.0f && x + step > -90.0f) {
            x += step;
        } else {
            return;
        }
        focus = Normalize(RotateVector(focus, axis, step));
    } else if (axis == Y) {
        angle += step;
    }

    frustum.rotate(position, axis, step);
}

Vector Camera::getFocus(void) const {
    return Normalize(RotateVector(focus, Y, angle));
}

void Camera::moveLeft(float step) {
    translate(Normalize(CrossProduct(Vector(0.0f, 1.0f, 0.0f), getFocus())) * std::fabs(step));
}

void Camera::moveRight(float step) {
    translate(Normalize(CrossProduct(Vector(0.0f, 1.0f, 0.0f), getFocus())) * -std::fabs(step));
}

void Camera::moveUp(float step) {
    translate(Vector(0.0f, std::fabs(step), 0.0f));
}

void Camera::moveDown(float step) {
    translate(Vector(0.0f, -std::fabs(step), 0.0f));
}

void Camera::moveForward(float step) {
    translate(Normalize(Vector(getFocus()[X], 0.0f, getFocus()[Z])) * std::fabs(step));
}

void Camera::moveBackward(float step) {
    translate(Normalize(Vector(getFocus()[X], 0.0f, getFocus()[Z])) * -std::fabs(step));
}

void Camera::rotateUp(float step) {
    rotate(X, std::fabs(step));
}

void Camera::rotateDown(float step) {
    rotate(X, -std::fabs(step));
}

void Camera::rotateLeft(float step) {
    rotate(Y, std::fabs(step));
}

void Camera::rotateRight(float step) {
    rotate(Y, -std::fabs(step));
}

const Vector& Camera::getPosition(void) const {
    return position;
}

Vector Camera::getVisiblePosition(void) const {
    return position + Normalize(focus) * frustum.near_dist;
}

#ifdef __DEBUG__
static void CameraCallbackKey(int key);

enum {
    KeyK = 'K',
    KeyF = 'F',
    KeyW = 'W',
    KeyA = 'A',
    KeyS = 'S',
    KeyD = 'D',
    Esc = 27,
    Plus = '+',
    Minus = '-',
    Up = 256 + GLUT_KEY_UP,
    Down = 256 + GLUT_KEY_DOWN,
    Left = 256 + GLUT_KEY_LEFT,
    Right = 256 + GLUT_KEY_RIGHT
};

static const float move_step = 9.0f;
static const float rotation_step = 5.0f;

void GLUTCameraCallback(int key, bool ascii) {
    CameraCallbackKey((ascii) ? std::toupper(key) : key + 256);
}

static void CameraCallbackKey(int key) {
    if (!current_camera) {
        return;
    }
    float step = move_step;

    switch (key) {
    case Esc:
        std::exit(0);
        break;
    case 'F':
        weapon.putaway();
        break;
    case 'K':
        detect_collisions = !detect_collisions;
        break;
    case Left:
        current_camera->rotateLeft(step);
        break;
    case Right:
        current_camera->rotateRight(step);
        break;
    case Down:
        current_camera->rotateDown(step);
        break;
    case Up:
        current_camera->rotateUp(step);
        break;
    case Plus:
        current_camera->moveUp(step);
        break;
    case Minus:
        current_camera->moveDown(step);
        break;
    case KeyW:
        current_camera->moveForward(step);
        break;
    case KeyS:
        current_camera->moveBackward(step);
        break;
    case KeyA:
        current_camera->moveLeft(step);
        break;
    case KeyD:
        current_camera->moveRight(step);
        break;
    }
}

void CameraCallback(int x, int y) {
    if (!current_camera) {
        return;
    }
    static Vector last;
    static bool first_mouse = true;
    static const float step = rotation_step;

    if (first_mouse) {
        last[X] = x;
        last[Y] = y;
        first_mouse = false;
        return;
    }

    if (x - last[X] < 0)
        current_camera->rotateLeft(step);
    else if (x - last[X] > 0)
        current_camera->rotateRight(step);

    if (y - last[Y] < 0)
        current_camera->rotateUp(step);
    else if (y - last[Y] > 0)
        current_camera->rotateDown(step);

    last[X] = x;
    last[Y] = y;

    int win_w = glutGet(GLUT_WINDOW_WIDTH);
    int win_h = glutGet(GLUT_WINDOW_HEIGHT);
    if (win_w > 0 && win_h > 0) {
        if (x > win_w * 0.75f || x < win_w * 0.25f || y > win_h * 0.75f || y < win_h * 0.25f) {
            last[X] = win_w / 2;
            last[Y] = win_h / 2;
            glutWarpPointer(win_w / 2, win_h / 2);
        }
    }

    glutPostRedisplay();
}

#ifndef GLUT_WHEEL_UP
#define GLUT_WHEEL_UP 3
#define GLUT_WHEEL_DOWN 4
#endif

void CameraCallback(int button, int state, int x, int y) {
    if (!current_camera) {
        return;
    }
    if (button == GLUT_WHEEL_DOWN) {
        current_camera->moveDown(move_step * 2);
    } else if (button == GLUT_WHEEL_UP) {
        current_camera->moveUp(move_step * 2);
    }

    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            weapon.startShooting();
        } else {
            weapon.stopShooting();
        }
    }
    CameraCallback(x, y);
}
#endif
