#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "Bounding_box.hpp"
#include "Plane.hpp"

namespace bgl {

	class ViewingFrustum : public OBB {
	private: public:
		float angles[2];
		float width;
		float height;
		float near;
		float far;
		Vector unrotated_vertices[8];
		Vector apex;
	public:
		ViewingFrustum(float width, float height, float near, float far);
		ViewingFrustum();
		void set(void) const;
		bool isWithin(const Vector& P) const;
		const Vector& getApex(void) const;
		Vector getViewDirection(void);
		void translate(const Vector& v);
		void rotate(const Vector& v, Axis axis, float angle);
		void calculatePlanes(void);

		void calculateVertices(void);
		//using OBB::intersects
		bool isWithin(const AABB& rhs) const;
		bool isWithin(void) const;
	};


	class Frustum {
	private:
		Plane planes[6];
	public:
		bool intersects(const BoundingBox& aabb) const
		{
			for (auto i = 0; i < 6; ++i) {
				for (auto j = 0; j < 8; ++j) {
					if (planes[i].contains(aabb.operator[](j))) {
						return true;
					}
				}
			}
			return false;
		}
	};

}  // namespace bgl

#endif  // FRUSTUM_H
