#ifndef BRUSH_H_
#define BRUSH_H_

#include "BSP.h"
#include "BoundingBox.h"
#include "GLee.h"
#include "Plane.h"
#include "Windows.h"
#include <vector>


class Brush {
public:
  Brush(void);
  Brush(const dbrush_t &brush, const dbrushside_t *brushsides,
        const dplane_t *planes);

  bool isWithin(const Vector &P) const;
  bool intersects(const AABB &rhs) const;
  bool intersects(const BoundingSphere &rhs) const;

private:
  std::vector<Plane> planes;
  int contents;
};

#endif // BRUSH_H_
