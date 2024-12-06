#ifndef BRUSH_H_
#define BRUSH_H_

#include "bounding_box.hpp"
#include "plane.hpp"
#include "BSP.hpp"

#include <vector>

namespace bgl {
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

}  // namespace bgl
#endif  // BRUSH_H_
