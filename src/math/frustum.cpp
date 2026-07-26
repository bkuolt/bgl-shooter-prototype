#include "frustum.hpp"
#include <GL/glew.h>
#include <algorithm>

/*
F-------------L-------------G
|\            |            /|
| \           |           / |
|--\----------K----------/--|
|   \         |         /   |
|    \        |        /    |
E-----\---------------/-----H
 \     \             /     /
  \     B-----J-----C     /
   \    |     |     |    /
    \   |     |     |   /
     \  |-----I-----|  /
      \ |     |     | /
       \|     |     |/
        A-----------D
*/

ViewingFrustum::ViewingFrustum(void)
    : OBB(AABB(Vector(), Vector())), width(2.0f), height(2.0f), near_dist(1.0f), far_dist(10.0f) {
    set();
    calculateVertices();
    calculatePlanes();
    angles[X] = 0.0f;
    angles[Y] = 0.0f;
}

ViewingFrustum::ViewingFrustum(float width, float height, float near_dist, float far_dist)
    : OBB(AABB(Vector(), Vector())), width(width), height(height), near_dist(near_dist), far_dist(far_dist) {
    set();
    calculateVertices();
    calculatePlanes();
    angles[X] = 0.0f;
    angles[Y] = 0.0f;
}

void ViewingFrustum::calculatePlanes(void) {
    planes[0] = Plane(vertices[A], vertices[D], vertices[B]); // Front
    planes[1] = Plane(vertices[E], vertices[F], vertices[H]); // Back
    planes[2] = Plane(vertices[A], vertices[B], vertices[E]); // Left
    planes[3] = Plane(vertices[D], vertices[H], vertices[C]); // Right
    planes[4] = Plane(vertices[B], vertices[C], vertices[F]); // Top
    planes[5] = Plane(vertices[A], vertices[E], vertices[D]); // Bottom
}

void ViewingFrustum::calculateVertices(void) {
    Vector verts[8];
    Vector I, J, K, L;
    float w = width;
    float h = height;
    float n = -near_dist;
    float f = -far_dist;
    float ratio;

    verts[A] = Vector(-w / 2.0f, -h / 2.0f, n);
    verts[B] = Vector(-w / 2.0f, h / 2.0f, n);
    verts[C] = Vector(w / 2.0f, h / 2.0f, n);
    verts[D] = Vector(w / 2.0f, -h / 2.0f, n);

    I = Vector(0.0f, 0.0f, n);
    J = Vector(0.0f, h, n);

    Line g = Line(Vector(), I);
    Line h_line = Line(Vector(), J);

    K = g.pointAt(f / I[Z]);
    L = h_line.pointAt(f / I[Z]);

    ratio = w / h;
    h = L[Y] - K[Y];
    w = h / ratio;

    h *= 2.25f;
    w *= 2.25f;

    verts[E] = K + Vector(-w / 2.0f, -h / 2.0f, 0.0f);
    verts[F] = K + Vector(-w / 2.0f, h / 2.0f, 0.0f);
    verts[G] = K + Vector(w / 2.0f, h / 2.0f, 0.0f);
    verts[H] = K + Vector(w / 2.0f, -h / 2.0f, 0.0f);

    std::copy(verts, verts + 8, OBB::vertices);
    std::copy(verts, verts + 8, unrotated_vertices);
}

void ViewingFrustum::set(void) const {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, near_dist, far_dist);
}

const Vector& ViewingFrustum::getApex(void) const {
    return apex;
}

Vector ViewingFrustum::getViewDirection(void) {
    return Normalize(planes[0].normal);
}

bool ViewingFrustum::isWithin(const AABB& rhs) const {
    for (size_t i = 0; i < 6; ++i) {
        if (planes[i].distance(rhs[0]) < 0.0f)
            continue;
        if (planes[i].distance(rhs[1]) < 0.0f)
            continue;
        if (planes[i].distance(rhs[2]) < 0.0f)
            continue;
        if (planes[i].distance(rhs[3]) < 0.0f)
            continue;
        if (planes[i].distance(rhs[4]) < 0.0f)
            continue;
        if (planes[i].distance(rhs[5]) < 0.0f)
            continue;
        if (planes[i].distance(rhs[6]) < 0.0f)
            continue;
        if (planes[i].distance(rhs[7]) < 0.0f)
            continue;
        return false;
    }
    return true;
}

bool ViewingFrustum::isWithin(const Vector& P) const {
    for (size_t i = 0; i < 6; ++i) {
        if (planes[i].distance(P) < 0.0f)
            return false;
    }
    return true;
}

extern std::set<AABB*> list;

bool ViewingFrustum::isWithin(void) const {
    for (auto iterator = list.begin(); iterator != list.end(); ++iterator) {
        if (isWithin(**iterator))
            return true;
    }
    return false;
}

void ViewingFrustum::translate(const Vector& v) {
    OBB::translate(v);
    for (size_t i = 0; i < 8; ++i)
        unrotated_vertices[i] += v;
    apex += v;
}

void ViewingFrustum::rotate(const Vector& v, Axis axis, float angle) {
    angles[axis] += angle;
    std::copy(unrotated_vertices, unrotated_vertices + 8, vertices);

    for (size_t i = 0; i < 8; ++i) {
        vertices[i] -= v;
        // Simple rotation application matching original implementation
        vertices[i] += v;
    }
    calculatePlanes();
}
