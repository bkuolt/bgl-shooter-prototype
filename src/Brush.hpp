#ifndef BRUSH_H_
#define BRUSH_H_

#include "BoundingBox.hpp"
#include "Plane.hpp"
#include "BSP.hpp"

#include <vector>

class Brush {
public:
	Brush(void);
	Brush(const dbrush_t& brush, const dbrushside_t* brushsides, const dplane_t* planes);

	bool isWithin(const Vector& P) const;
	bool intersects(const AABB& rhs) const;
	bool intersects(const BoundingSphere& rhs) const;
private:
	std::vector<Plane> planes;
	int contents;
};

#endif  // BRUSH_H_
