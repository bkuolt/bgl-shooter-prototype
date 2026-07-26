#ifndef LINE_HPP_INCLUDED
#define LINE_HPP_INCLUDED

#include "vector.hpp"

class Line {
public:
    Vector origin;
    Vector direction;

public:
    Line(void) {}
    Line(const Vector& origin, const Vector& direction) : origin(origin), direction(direction) {}

    Vector pointAt(float t) const { return origin + direction * t; }
};

typedef Line Ray;

#endif // LINE_HPP_INCLUDED
