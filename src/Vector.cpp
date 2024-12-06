#include "Vector.hpp"


Vector& Vector::operator+=(const Vector& rhs) {
	values[0] += rhs.values[0];
	values[1] += rhs.values[1];
	values[2] += rhs.values[2];
	return *this;
}

Vector& Vector::operator-=(const Vector& rhs) {
	values[0] -= rhs.values[0];
	values[1] -= rhs.values[1];
	values[2] -= rhs.values[2];
	return *this;
}

Vector& Vector::operator*=(const Vector& rhs) {
	values[0] *= rhs.values[0];
	values[1] *= rhs.values[1];
	values[2] *= rhs.values[2];
	return *this;
}

Vector& Vector::operator*=(float k) {
	values[0] *= k;
	values[1] *= k;
	values[2] *= k;
	return *this;
}

Vector Vector::operator+(const Vector& rhs) const {
	return Vector(*this) += rhs;
}

Vector Vector::operator-(const Vector& rhs) const {
	return Vector(*this) -= rhs;
}

Vector Vector::operator-(const Vector& rhs) {
	return Vector(*this) -= rhs;
}

Vector Vector::operator+(const Vector& rhs) {
	return Vector(*this) += rhs;
}

Vector Vector::operator*(float k) const {
	return Vector(*this) *= k;
}

Vector Vector::operator*(float k) {
	return Vector(*this) *= k;
}

float Vector::length(void) const {
	return std::sqrt(values[X] * values[X] +
		values[Y] * values[Y] +
		values[Z] * values[Z]);
}

Vector Vector::normalize(void) {
	return *this *= (1.0f / length());
}

/*
==============================================
Rotationen
==============================================*/
Vector Vector::rotate(int axis, float angle) {
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

Vector Vector::rotate(int axis, float angle) const {
	Vector v(*this);
	v.rotate(axis, angle);
	return v;
}

void Vector::rotate(const Vector& v, int axis, float angle) {
	// *this -= v;
	rotate(axis, angle);
	// *this += v;
}

const float* Vector::begin(void) const {
	return values.data();
}

float* Vector::begin(void) {
	return values.data();
}

const float* Vector::end(void) const {
	return values.data() + 3;
}

float* Vector::end(void) {
	return values.data() + 3;
}


bool Vector::operator==(const Vector& rhs) const {
	return rhs[Axis::X] == values[Axis::X] &&
		rhs[Axis::Y] == values[Axis::Y] &&
		rhs[Axis::Z] == values[Axis::Z];
}