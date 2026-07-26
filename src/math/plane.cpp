#include "plane.hpp"
#include <GL/freeglut.h>
#include <GL/glew.h>
#include <cmath>

Plane::Plane(const Vector& normal, const Vector& point) {
    this->normal = normal;
    this->dist = DotProduct(normal, point);
}

Plane::Plane(const Vector& p1, const Vector& p2, const Vector& p3) {
    Vector v1 = p2 - p1;
    Vector v2 = p3 - p1;
    this->normal = Normalize(CrossProduct(v1, v2));
    this->dist = DotProduct(this->normal, p1);
}

float Plane::distance(const Vector& point) const {
    return DotProduct(normal, point) - dist;
}

bool Plane::isFrontFacing(const Vector& point) const {
    return distance(point) >= 0.0f;
}

Plane& Plane::translate(const Vector& v) {
    dist += DotProduct(normal, v);
    return *this;
}

Plane& Plane::rotate(Axis axis, float angle) {
    normal = RotateVector(normal, axis, angle);
    return *this;
}

void Plane::draw(float width, float height) const {
    // Debug draw plane helper if needed
}
