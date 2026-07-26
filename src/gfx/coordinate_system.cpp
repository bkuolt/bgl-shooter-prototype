#include "coordinate_system.hpp"
#include <GL/glew.h>

CoordinateSystem::CoordinateSystem(void) : XAxis(1.0f, 0.0f, 0.0f), YAxis(0.0f, 1.0f, 0.0f), ZAxis(0.0f, 0.0f, 1.0f) {}

CoordinateSystem::CoordinateSystem(const Vector& x, const Vector& y, const Vector& z) : XAxis(x), YAxis(y), ZAxis(z) {}

CoordinateSystem& CoordinateSystem::rotate(Axis axis, float angle) {
    XAxis = RotateVector(XAxis, axis, angle);
    YAxis = RotateVector(YAxis, axis, angle);
    ZAxis = RotateVector(ZAxis, axis, angle);
    return *this;
}

void CoordinateSystem::draw(void) const {
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(XAxis[X], XAxis[Y], XAxis[Z]);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(YAxis[X], YAxis[Y], YAxis[Z]);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(ZAxis[X], ZAxis[Y], ZAxis[Z]);
    glEnd();
}
