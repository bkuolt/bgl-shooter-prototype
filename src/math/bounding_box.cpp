#include "bounding_box.hpp"
#include <GL/freeglut.h>
#include <GL/glew.h>
#include <cmath>

#ifdef __DEBUG__
std::set<AABB*> list;
#endif

/*
  F-------G
/ |      /|
B-------C |
| |     | |
| E-----|-H
|/      |/
A-------D
*/

AxisAlignedBoundingBox::AxisAlignedBoundingBox(const Vector& min, const Vector& max) {
    calculateVertices(min, max);
    calculatePlanes();
    translate(min - vertices[A]);
}

AxisAlignedBoundingBox::AxisAlignedBoundingBox(float width, float height, float depth, const Vector& center) {
    calculateVertices(center + Vector(-width / 2.0f, -height / 2.0f, -depth / 2.0f),
                      center + Vector(width / 2.0f, height / 2.0f, depth / 2.0f));
    calculatePlanes();
}

#ifdef __DEBUG__
AxisAlignedBoundingBox::AxisAlignedBoundingBox(const float* vertices, size_t count) {
    Vector min, max;

    for (size_t i = 0; i < count; ++i) {
        for (size_t c = 0; c < 3; ++c) {
            if (vertices[(i * 3) + c] > max[c])
                max[c] = vertices[(i * 3) + c];
            else if (vertices[(i * 3) + c] < min[c])
                min[c] = vertices[(i * 3) + c];
        }
    }

    calculateVertices(min, max);
    calculatePlanes();
}

void AxisAlignedBoundingBox::manage(void) {
    list.insert(this);
}

AxisAlignedBoundingBox::~AxisAlignedBoundingBox(void) {
    list.erase(this);
}
#endif

void AxisAlignedBoundingBox::calculateVertices(const Vector& min, const Vector& max) {
    Vector center = getCenter();
    float width = std::fabs(max[X] - min[X]);
    float height = std::fabs(max[Y] - min[Y]);
    float depth = std::fabs(max[Z] - min[Z]);

    vertices[A] = center + Vector(-width / 2.0f, -height / 2.0f, depth / 2.0f);
    vertices[B] = center + Vector(-width / 2.0f, height / 2.0f, depth / 2.0f);
    vertices[C] = center + Vector(width / 2.0f, height / 2.0f, depth / 2.0f);
    vertices[D] = center + Vector(width / 2.0f, -height / 2.0f, depth / 2.0f);
    vertices[E] = center + Vector(-width / 2.0f, -height / 2.0f, -depth / 2.0f);
    vertices[F] = center + Vector(-width / 2.0f, height / 2.0f, -depth / 2.0f);
    vertices[G] = center + Vector(width / 2.0f, height / 2.0f, -depth / 2.0f);
    vertices[H] = center + Vector(width / 2.0f, -height / 2.0f, -depth / 2.0f);
}

void AxisAlignedBoundingBox::calculatePlanes(void) {
    planes[0] = Plane(vertices[A], vertices[D], vertices[B]); // Front
    planes[1] = Plane(vertices[E], vertices[F], vertices[H]); // Back
    planes[2] = Plane(vertices[A], vertices[B], vertices[E]); // Left
    planes[3] = Plane(vertices[D], vertices[H], vertices[C]); // Right
    planes[4] = Plane(vertices[B], vertices[C], vertices[F]); // Top
    planes[5] = Plane(vertices[A], vertices[E], vertices[D]); // Bottom
}

bool AxisAlignedBoundingBox::intersects(const Ray& ray) const {
    return false;
}

bool AxisAlignedBoundingBox::intersects(const AxisAlignedBoundingBox& rhs) const {
    Vector distance = getCenter() - rhs.getCenter();

    if (std::fabs(distance[X]) > std::fabs(getWidth() + rhs.getWidth()))
        return false;
    if (std::fabs(distance[Y]) > std::fabs(getHeight() + rhs.getHeight()))
        return false;
    if (std::fabs(distance[Z]) > std::fabs(getDepth() + rhs.getDepth()))
        return false;
    return true;
}

bool AxisAlignedBoundingBox::isWithin(const Vector& v) const {
    return (vertices[A][X] < v[X] && vertices[D][X] > v[X]) && (vertices[A][Y] < v[Y] && vertices[B][Y] > v[Y]) &&
           (vertices[A][Z] > v[Z] && vertices[E][Z] < v[Z]);
}

AxisAlignedBoundingBox& AxisAlignedBoundingBox::translate(const Vector& v) {
    for (size_t i = 0; i < 8; ++i)
        vertices[i] += v;
    for (size_t i = 0; i < 6; ++i)
        planes[i].translate(v);
    return *this;
}

Vector AxisAlignedBoundingBox::getCenter(void) const {
    return vertices[A] + (vertices[G] - vertices[A]) * 0.5f;
}

void AxisAlignedBoundingBox::position(const Vector& v) {
    translate(v - getCenter());
}

float AxisAlignedBoundingBox::getWidth(void) const {
    return std::fabs(vertices[D][X] - vertices[A][X]);
}

float AxisAlignedBoundingBox::getHeight(void) const {
    return std::fabs(vertices[B][Y] - vertices[A][Y]);
}

float AxisAlignedBoundingBox::getDepth(void) const {
    return std::fabs(vertices[E][Z] - vertices[A][Z]);
}

const Plane& AxisAlignedBoundingBox::getPlane(size_t i) const {
    return planes[i];
}

#ifdef __DEBUG__
void AxisAlignedBoundingBox::draw(void) const {
    static const GLubyte indices[] = {0, 1, 2, 3, 0, 3, 4, 5, 0, 5, 6, 1, 1, 6, 7, 2, 7, 4, 3, 2, 4, 7, 6, 5};

    GLfloat points[24] = {vertices[C][X], vertices[C][Y], vertices[C][Z], vertices[B][X], vertices[B][Y],
                          vertices[B][Z], vertices[A][X], vertices[A][Y], vertices[A][Z], vertices[D][X],
                          vertices[D][Y], vertices[D][Z], vertices[H][X], vertices[H][Y], vertices[H][Z],
                          vertices[G][X], vertices[G][Y], vertices[G][Z], vertices[F][X], vertices[F][Y],
                          vertices[F][Z], vertices[E][X], vertices[E][Y], vertices[E][Z]};

    glPushAttrib(GL_CURRENT_BIT | GL_POLYGON_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(1.0f, 0.0f, 0.0f);

    glVertexPointer(3, GL_FLOAT, 0, points);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopAttrib();
}
#endif

OBB::OBB(const AxisAlignedBoundingBox& aabb) : AxisAlignedBoundingBox(aabb) {}

bool OBB::isWithin(const Vector& P) const {
    for (size_t i = 0; i < 6; ++i)
        if (planes[i].distance(P) > 0.0f)
            return false;
    return true;
}

bool OBB::intersects(const AxisAlignedBoundingBox& rhs) const {
    for (size_t i = 0; i < 8; ++i)
        if (isWithin(rhs.vertices[i]) || rhs.isWithin(vertices[i]))
            return true;
    return false;
}

OBB& OBB::rotate(Axis axis, float angle) {
    Vector center = getCenter();
    for (size_t i = 0; i < 8; ++i) {
        vertices[i] -= center;
        vertices[i] += center;
    }
    calculatePlanes();
    return *this;
}

bool AxisAlignedBoundingBox::intersects(const BoundingSphere& sphere) const {
    for (size_t i = 0; i < 6; ++i)
        if (planes[i].distance(sphere.getCenter()) < sphere.getRadius())
            return true;
    return false;
}

BoundingSphere::BoundingSphere(const Vector& center, float radius) : center(center), radius(radius) {}

bool BoundingSphere::intersects(const BoundingSphere& rhs) const {
    return Length(center - rhs.center) < radius + rhs.radius;
}

BoundingSphere& BoundingSphere::translate(const Vector& v) {
    center += v;
    return *this;
}

float BoundingSphere::getRadius(void) const {
    return radius;
}

const Vector& BoundingSphere::getCenter(void) const {
    return center;
}

#ifdef __DEBUG__
void BoundingSphere::draw(void) const {
    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();
    glTranslatef(center[X], center[Y], center[Z]);
    glScalef(radius, radius, radius);
    glColor3f(0.0f, 0.0f, 1.0f);
    glutWireSphere(1, 50, 50);
    glPopMatrix();
    glPopAttrib();
}
#endif
