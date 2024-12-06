#ifndef __VECTOR_H__
#define __VECTOR_H__


#include <cmath>
#include <cstdlib>
#include <array>

#define M_PI 3.14159265358979323846


inline float RadianToDegree(float angle) {
	return angle * (180.0f / M_PI);
}

constexpr int X = 0;
constexpr int Y = 1;
constexpr int Z = 2;


class Vector {
private:
	const int X = 0;
	const int Y = 1;
	const int Z = 2;

	std::array<float, 3> values;

public:
	Vector(float x, float y, float z = 0.0f) {
		values[0] = x;
		values[1] = y;
		values[2] = z;
	}

	Vector(void) {
		values[0] = values[1] = values[2] = 0.0f;
	}

	float& operator[](unsigned int axis) noexcept {
		return values[axis];
	}

	const float& operator[](unsigned int axis) const noexcept {
		return values[axis];
	}

	Vector& operator+=(const Vector& rhs) {
		values[0] += rhs.values[0];
		values[1] += rhs.values[1];
		values[2] += rhs.values[2];
		return *this;
	}

	Vector& operator-=(const Vector& rhs) {
		values[0] -= rhs.values[0];
		values[1] -= rhs.values[1];
		values[2] -= rhs.values[2];
		return *this;
	}

	Vector& operator*=(const Vector& rhs) {
		values[0] *= rhs.values[0];
		values[1] *= rhs.values[1];
		values[2] *= rhs.values[2];
		return *this;
	}

	Vector& operator*=(float k) {
		values[0] *= k;
		values[1] *= k;
		values[2] *= k;
		return *this;
	}

	Vector operator+(const Vector& rhs) const {
		return Vector(*this) += rhs;
	}

	Vector operator-(const Vector& rhs) const {
		return Vector(*this) -= rhs;
	}

	Vector operator-(const Vector& rhs) {
		return Vector(*this) -= rhs;
	}

	Vector operator+(const Vector& rhs) {
		return Vector(*this) += rhs;
	}

	Vector operator*(float k) const {
		return Vector(*this) *= k;
	}

	Vector operator*(float k) {
		return Vector(*this) *= k;
	}

	float length(void) const {
		return std::sqrt(values[X] * values[X] +
			values[Y] * values[Y] +
			values[Z] * values[Z]);
	}

	Vector& normalize(void) {
		return *this *= (1.0f / length());
	}

	/*
	==============================================
	Rotationen
	==============================================*/
	Vector& rotate(int axis, float angle) {
		Vector v(*this); // Kopie des Vektors
		angle = angle *= (M_PI / 180); // Grad in Bogenma�

		switch (axis) {
		case 0:
			values[Y] = v[Y] * cos(angle) - v[Z] * sin(angle);
			values[Z] = v[Y] * sin(angle) + v[Z] * cos(angle);
			break;
		case 1:
			values[X] = v[Z] * sin(angle) + v[X] * cos(angle);
			values[Z] = v[Z] * cos(angle) - v[X] * sin(angle);
			break;
		case 2:
			values[X] = v[X] * cos(angle) - v[Y] * sin(angle);
			values[Y] = v[X] * sin(angle) + v[Y] * cos(angle);
			break;
		}
		return *this;
	}

	Vector rotate(int axis, float angle) const {
		Vector v(*this);
		v.rotate(axis, angle);
		return v;
	}

	void rotate(const Vector& v, int axis, float angle) {
		// *this -= v;
		rotate(axis, angle);
		// *this += v;
	}

	const float* begin(void) const {
		return values.data();
	}

	float* begin(void) {
		return values.data();
	}

	const float* end(void) const {
		return values.data() + 3;
	}

	float* end(void) {
		return values.data() +3;
	}

	/*
	=================================================================
	Projeziert diesen Vektor auf den angegebenen Vektor
	=================================================================*/
	Vector project(const Vector& v) const {
		return (v * DotProduct(*this, v)) * (1.0f / v.length());
	}


	bool operator==(const Vector& rhs) const {
		return rhs[X] == values[X] &&
			rhs[Y] == values[Y] &&
			rhs[Z] == values[Z];
	}
};
//----------------------------------------------------------------
inline float ScalarMultiple(const Vector& u, const Vector& v) {
	// u   = s*v
	// u/v = s
	if (v[X] != 0)
		return u[X] / v[X];
	if (v[Y] != 0)
		return u[Y] / v[Y];
	if (v[Z] != 0)
		return u[Z] / v[Z];
}

inline float DotProduct(const Vector& a, const Vector& b) {
	return (a[X] * b[X]) + (a[Y] * b[Y]) + (a[Z] * b[Z]);
}

inline Vector CrossProduct(const Vector& a, const Vector& b) {
	return Vector(a[1] * b[2] - b[1] * a[2],
		a[2] * b[0] - b[2] * a[0],
		a[0] * b[1] - b[0] * a[1]);
}

inline float Angle(const Vector& a, const Vector& b) {
	return RadianToDegree(acos(DotProduct(a, b) / (a.length() * b.length())));
}

inline bool AreCollinear(const Vector& a, const Vector& b) {
	return (a[0] / b[0] == a[1] / b[2]) == a[2] / b[2];
}

inline Vector Center(const Vector& a, const Vector& b) {
	return a + (b - a) * 0.5f;
}


inline float DotProduct(const Vector& a, const Vector& b);
inline float Angle(const Vector& a, const Vector& b);


#endif
