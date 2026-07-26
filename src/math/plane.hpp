#ifndef PLANE_HPP_INCLUDED
#define PLANE_HPP_INCLUDED

#include "vector.hpp"
#include <GL/glew.h>

class Plane {
public:
    Vector normal;
    float dist;

public:
    Plane(void) : dist(0.0f) {}
    Plane(const Vector& normal, float dist) : normal(normal), dist(dist) {}
    Plane(const Vector& normal, const Vector& point);
    Plane(const Vector& p1, const Vector& p2, const Vector& p3);

    float distance(const Vector& point) const;
    bool isFrontFacing(const Vector& point) const;

    Plane& translate(const Vector& v);
    Plane& rotate(Axis axis, float angle);

    void draw(float width, float height) const;
};

#endif // PLANE_HPP_INCLUDED
