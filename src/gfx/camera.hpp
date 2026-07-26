#ifndef CAMERA_HPP_INCLUDED
#define CAMERA_HPP_INCLUDED

#include "bounding_box.hpp"
#include "coordinate_system.hpp"
#include "frustum.hpp"
#include "vector.hpp"

class Camera {
public:
    BoundingSphere sphere;
    float angle;
    CoordinateSystem axes;
    ViewingFrustum frustum;
    Vector position;
    Vector focus;

public:
    Camera(void);
    Camera(const ViewingFrustum& frustum);
    Camera(const Vector& position, const Vector& focus, const ViewingFrustum& frustum);

    Vector getFocus(void) const;
    void calculateBoundingSphere(void);
    void set(void) const;

    void translate(const Vector& v);
    void setPosition(const Vector& p);
    void rotate(Axis axis, float step);

    const Vector& getPosition(void) const;
    Vector getVisiblePosition(void) const;

    void moveLeft(float step);
    void moveRight(float step);
    void moveUp(float step);
    void moveDown(float step);
    void moveForward(float step);
    void moveBackward(float step);
    void rotateUp(float step);
    void rotateDown(float step);
    void rotateLeft(float step);
    void rotateRight(float step);
};

void GLUTCameraCallback(int key, bool ascii);
void CameraCallback(int x, int y);
void CameraCallback(int button, int state, int x, int y);

namespace CD {
bool WouldHaveWallCollision(const Vector& v);
}

#endif // CAMERA_HPP_INCLUDED
