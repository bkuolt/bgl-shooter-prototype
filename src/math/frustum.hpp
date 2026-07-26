#ifndef FRUSTUM_HPP_INCLUDED
#define FRUSTUM_HPP_INCLUDED

#include "bounding_box.hpp"
#include "line.hpp"
#include "plane.hpp"
#include "vector.hpp"

class ViewingFrustum : public OBB {
public:
    float angles[2];
    float width;
    float height;
    float near_dist;
    float far_dist;
    Vector unrotated_vertices[8];
    Vector apex;

public:
    ViewingFrustum();
    ViewingFrustum(float width, float height, float near_dist, float far_dist);

    void set(void) const;
    bool isWithin(const Vector& P) const;
    bool isWithin(const AABB& rhs) const;
    bool isWithin(void) const;
    const Vector& getApex(void) const;
    Vector getViewDirection(void);
    void translate(const Vector& v);
    void rotate(const Vector& v, Axis axis, float angle);
    void calculatePlanes(void);
    void calculateVertices(void);
};

#endif // FRUSTUM_HPP_INCLUDED
