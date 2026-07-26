#include "brush.hpp"

Brush::Brush(void) : contents(0) {}

Brush::Brush(const dbrush_t& brush, const dbrushside_t* brushsides, const dplane_t* planes) : contents(brush.contents) {
    for (int i = 0; i < brush.numsides; ++i) {
        int side_idx = brush.firstside + i;
        int plane_idx = brushsides[side_idx].planenum;
        const dplane_t& dp = planes[plane_idx];
        this->planes.push_back(Plane(Vector(dp.normal[0], dp.normal[1], dp.normal[2]), dp.dist));
    }
}

bool Brush::isWithin(const Vector& P) const {
    for (size_t i = 0; i < planes.size(); ++i) {
        if (planes[i].distance(P) > 0.0f)
            return false;
    }
    return true;
}

bool Brush::intersects(const AABB& rhs) const {
    for (size_t i = 0; i < 8; ++i) {
        if (isWithin(rhs.vertices[i]))
            return true;
    }
    return false;
}

bool Brush::intersects(const BoundingSphere& rhs) const {
    for (size_t i = 0; i < planes.size(); ++i) {
        if (planes[i].distance(rhs.getCenter()) > rhs.getRadius())
            return false;
    }
    return true;
}
