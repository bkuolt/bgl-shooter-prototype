#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "BoundingBox.h"
#include "Plane.hpp"

class Frustum {
private:
	Plane planes[6];
public:
	bool intersects(const AxisAlignedBoundingBox& aabb) const
	{
		for (auto i = 0; i < 6; ++i) {
			for (auto j = 0; j < 8; ++j) {
				if (planes[i].contains(aabb.operator[](j) )) {
					return true;
				}
			}
		}
		return false;
	}
};
#endif  // FRUSTUM_H
