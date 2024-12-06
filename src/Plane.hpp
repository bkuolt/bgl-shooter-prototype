#ifndef PLANE_HPP
#define PLANE_HPP

#include "Line.hpp"
#include "Vector.hpp"

#include <cstdio>
#include <utility>

namespace bgl {

	class Plane {
	public:
		enum { A, B, C, D };
	public:
		Vector p, u, v;
		float equation[4];

	public:
		enum class Axis{ X, Y, Z };

		Plane();
		Plane(const Plane&) = default;
		Plane& operator=(const Plane&) = default;

		Plane(const Vector& P1, const Vector& P2, const Vector& P3);

		Plane(float a, float b, float c, float d);
		Vector getNormal(void) const;
		Vector invertNormal(void);

		Vector getOrigin(void);
		Plane& translate(const Vector& v);
		Vector getPoint(float s, float t) const;
		bool contains(const Vector& P) const;
		float distance(const Vector& P) const;

		bool isFrontFacing(const Vector& P) const;
		bool isBackFacing(const Vector& P) const;
		bool intersects(const Line& line) const;

		Vector getIntersection(const Line& line) const;
		std::pair<float, float> getParameters(const Vector& P) const;
		void rotate(Axis axis, float angle);
		void draw(float s, float t) const;
	};


} // namespace bgl

#endif   // PLANE_HPP
