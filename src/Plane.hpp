#ifndef PLANE_HPP
#define PLANE_HPP

#include "Line.h"
#include "Vector.h"

#include <cstdio>
#include <utility>


class Plane {
public:
	enum { A, B, C, D };
public:
	Vector p, u, v;
	float equation[4];

public:
	Plane();
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
#endif   // PLANE_HPP
