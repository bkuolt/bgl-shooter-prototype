#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>
#include <cstdlib>
#include <array>

#undef near  // TODO
#undef far   // 

#define M_PI 3.14159265358979323846


namespace bgl {


constexpr float RadianToDegree(float angle) {
	return angle * (180.0f / M_PI);
};


const int X = 0;
const int Y = 1;
const int Z = 2;


class Vector {
private:
	std::array<float, 3> values;


public:
	Vector(const Vector&) = default;
	Vector(Vector&&) = default;
	Vector& operator=(const Vector&) = default;
	Vector& operator=(Vector&&) = default;

	Vector(float x, float y, float z = 0.0f) {
		values[0] = x;
		values[1] = y;
		values[2] = z;
	}

	Vector(void) {
		values[0] = values[1] = values[2] = 0.0f;
	}

	float& operator[](int axis) noexcept {
		return values[axis];
	}

	const float& operator[](int axis) const noexcept {
		return values[axis];
	}

	Vector& operator+=(const Vector& rhs);
	Vector& operator-=(const Vector& rhs);
	Vector& operator*=(const Vector& rhs);
	Vector& operator*=(float k);
	Vector operator+(const Vector& rhs) const;
	Vector operator-(const Vector& rhs) const;
	Vector operator-(const Vector& rhs);
	Vector operator+(const Vector& rhs);
	Vector operator*(float k) const;
	Vector operator*(float k);

	float length(void) const;
	Vector normalize(void);
	Vector rotate(int axis, float angle);

};

using vec3 = Vector;


static inline float ScalarMultiple(const Vector& u, const Vector& v) {
	// u   = s*v
	// u/v = s
	if (v[X] != 0)
		return u[X] / v[X];
	if (v[Y] != 0)
		return u[Y] / v[Y];
	if (v[Z] != 0)
		return u[Z] / v[Z];
}

static inline float DotProduct(const Vector& a, const Vector& b) {
	return (a[X] * b[X]) + (a[Y] * b[Y]) + (a[Z] * b[Z]);
}

static inline Vector CrossProduct(const Vector& a, const Vector& b) {
	return Vector(a[1] * b[2] - b[1] * a[2],
		a[2] * b[0] - b[2] * a[0],
		a[0] * b[1] - b[0] * a[1]);
}

static inline float Angle(const Vector& a, const Vector& b) {
	return RadianToDegree(acos(DotProduct(a, b) / (a.length() * b.length())));
}

static inline bool AreCollinear(const Vector& a, const Vector& b) {
	return (a[0] / b[0] == a[1] / b[2]) == a[2] / b[2];
}

static inline Vector Center(const Vector& a, const Vector& b) {
	return a + (b - a) * 0.5f;
}

/*
=================================================================
Projeziert diesen Vektor auf den angegebenen Vektor
=================================================================*/
static inline Vector Project(const Vector& sis, const Vector& v) {

	return Vector();
	//return (v * DotProduct(sis, v)) * (1.0f / v.length());
}

}  // namespace bgl

#endif
