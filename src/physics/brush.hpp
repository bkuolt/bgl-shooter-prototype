#ifndef BRUSH_HPP_INCLUDED
#define BRUSH_HPP_INCLUDED

#include "bounding_box.hpp"
#include "bsp.hpp"
#include "plane.hpp"
#include "types.hpp"
#include <vector>

class Brush {
private:
    std::vector<Plane> planes;
    int contents;

public:
    Brush(void);
    Brush(const dbrush_t& brush, const dbrushside_t* brushsides, const dplane_t* planes);

    bool isWithin(const Vector& P) const;
    bool intersects(const AABB& rhs) const;
    bool intersects(const BoundingSphere& rhs) const;
};

#endif // BRUSH_HPP_INCLUDED
