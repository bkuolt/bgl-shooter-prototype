#ifndef BOUNDING_BOX_HPP_INCLUDED
#define BOUNDING_BOX_HPP_INCLUDED

#include "line.hpp"
#include "plane.hpp"
#include "vector.hpp"
#include <GL/glew.h>

#include <cstdio>
#include <set>

#define __DEBUG__

class BoundingBox {
public:
    enum Vertex { A, B, C, D, E, F, G, H };
    Vector vertices[8];

public:
    const Vector& operator[](size_t index) const;
    Vector& operator[](size_t index);
#ifdef __DEBUG__
    void draw(void) const;
#endif
};

class BoundingSphere {
private:
    Vector center;
    float radius;

public:
    BoundingSphere(void) : radius(0.0f) {}
    BoundingSphere(const Vector& center, float radius);

    bool intersects(const BoundingSphere& rhs) const;
    BoundingSphere& translate(const Vector& v);
    float getRadius(void) const;
    const Vector& getCenter(void) const;
    void draw(void) const;
};

class AxisAlignedBoundingBox : public BoundingBox {
public:
    Plane planes[6];

public:
    AxisAlignedBoundingBox() {}
    AxisAlignedBoundingBox(float width, float height, float depth, const Vector& center = Vector());
    AxisAlignedBoundingBox(const float* vertices, size_t count);
    AxisAlignedBoundingBox(const Vector& min, const Vector& max);
    ~AxisAlignedBoundingBox(void);

    void calculateVertices(const Vector& min, const Vector& max);
    Vector getCenter(void) const;
    float getWidth(void) const;
    float getHeight(void) const;
    float getDepth(void) const;
    Vector getRadius(void) const;
    AxisAlignedBoundingBox& translate(const Vector& v);
    AxisAlignedBoundingBox& scale(const Vector& v);
    AxisAlignedBoundingBox& scale(float k);
    bool intersects(const AxisAlignedBoundingBox& rhs) const;
    bool intersects(const Ray& rhs) const;
    void calculatePlanes();
    bool intersects(const BoundingSphere& sphere) const;

    bool isWithin(const Vector&) const;
    void manage(void);

    const Plane& getPlane(size_t i) const;
    void position(const Vector& v);

    const Vector& operator[](size_t i) const { return vertices[i]; }
    Vector& operator[](size_t i) { return vertices[i]; }

    void draw(void) const;
};

typedef AxisAlignedBoundingBox AABB;
typedef AxisAlignedBoundingBox OrientedBoundingVolume;

class OBB : public AxisAlignedBoundingBox {
public:
    OBB(const AxisAlignedBoundingBox& aabb);

    bool isWithin(const Vector& P) const;
    bool intersects(const AxisAlignedBoundingBox& rhs) const;
    OBB& rotate(Axis axis, float angle);

    bool intersects(const Ray& ray) const { return AxisAlignedBoundingBox::intersects(ray); }
};

#endif // BOUNDING_BOX_HPP_INCLUDED
