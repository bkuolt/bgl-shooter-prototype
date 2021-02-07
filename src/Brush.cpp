#include "Brush.h"

/*
=====================================================================
Konstruktoren
=====================================================================*/
Brush::Brush(void) : contents(0)
{}

Brush::Brush(const dbrush_t &brush, const dbrushside_t *brushsides, const dplane_t *planes)
    : contents(brush.contents) {
    size_t j;
    // (1) Reserviert Speicher für Ebenen
    Brush::planes.resize(brush.numsides);
    // (2) Liest Ebenen ein
    for (size_t i = 0; i < brush.numsides; ++i) {
        j = brushsides[brush.firstside + i].planenum;
        Brush::planes[i] = Plane(planes[j].normal[X], planes[j].normal[Y], planes[j].normal[Z], -planes[j].dist);
    }
}

/*
=====================================================================
�berpr�ft,ob sich Punkt im Volumen befindet
=====================================================================*/
bool Brush::isWithin(const Vector &P) const{
    if (contents & CONTENTS_SOLID) {
        for (size_t i = 0; i < planes.size(); ++i)
            if (planes[i].isFrontFacing(P))
                return false;
        return true;
    }
    else
        return false;
}

/*
=====================================================================
�berpr�ft,ob sich AABB im Volumen befindet
=====================================================================
"Alternatively since it's just plane box intersection you can find the signed distance to the plane for every
point on the box (+-Xx,+-Xy,+-Xz)and if all of those signs are the same then it lies completely on one side,
otherwise there is a collision."
(http://www.gamedev.net/topic/550461-aabb-plane-collision)
*/
bool Brush::intersects(const AABB &rhs) const {
    if (!(contents & CONTENTS_SOLID))
        return false;

    for (size_t i = 0; i < planes.size(); ++i) {
        if (planes[i].distance(rhs[0]) < 0.0f) continue;
        if (planes[i].distance(rhs[1]) < 0.0f) continue;
        if (planes[i].distance(rhs[2]) < 0.0f) continue;
        if (planes[i].distance(rhs[3]) < 0.0f) continue;
        if (planes[i].distance(rhs[4]) < 0.0f) continue;
        if (planes[i].distance(rhs[5]) < 0.0f) continue;
        if (planes[i].distance(rhs[6]) < 0.0f) continue;
        if (planes[i].distance(rhs[7]) < 0.0f) continue;
        return true;
    }
    return false;
}

/*
=====================================================================
Überprüft,ob sich BoundingSphere im Volumen befindet
HINWEIS: Noch nicht getestet
=====================================================================*/
bool Brush::intersects(const BoundingSphere &sphere) const {
    Vector center;
    float radius;

    if (contents & CONTENTS_DETAIL) return false;

    if (contents & CONTENTS_SOLID) {
        // (1) Berechnet Radius und Mittelpunkt
        center = sphere.getCenter();
        radius = fabs(sphere.getRadius());

        // (2) �berpr�ft,ob Abstand des Mittelpunkts der Kugel zu allen Ebenen kleiner als der radius ist
        for (size_t i = 0;i < planes.size();++i)
            if (planes[i].distance(center) >= radius)
                return false;
        return true;
     }
     else
        return false;
}
