#ifndef BRUSH_H_INCLUDED
#define BRUSH_H_INCLUDED

#include "Windows.h"
#include "GLee.h"
#include "BoundingBox.h"
#include "Plane.h"
#include "BSP.h"
#include <vector>

class Brush
{
    private:
        std::vector<Plane> planes;
        int contents;
    public:
        Brush(void);
        Brush(const dbrush_t &brush,const dbrushside_t *brushsides,const dplane_t *planes);
        bool isWithin(const Vector &P) const;
        bool intersects(const AABB &rhs) const;
        bool intersects(const BoundingSphere &rhs) const;
};
#endif
