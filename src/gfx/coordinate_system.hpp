#ifndef COORDINATE_SYSTEM_HPP_INCLUDED
#define COORDINATE_SYSTEM_HPP_INCLUDED

#include "vector.hpp"

class CoordinateSystem {
public:
    Vector XAxis;
    Vector YAxis;
    Vector ZAxis;

public:
    CoordinateSystem(void);
    CoordinateSystem(const Vector& x, const Vector& y, const Vector& z);

    CoordinateSystem& rotate(Axis axis, float angle);
    void draw(void) const;
};

#endif // COORDINATE_SYSTEM_HPP_INCLUDED
