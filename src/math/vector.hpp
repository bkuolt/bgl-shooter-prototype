#ifndef VECTOR_HPP_INCLUDED
#define VECTOR_HPP_INCLUDED

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

enum Axis { X = 0, Y = 1, Z = 2 };

using Vector = glm::vec3;

inline Vector Normalize(const Vector& v) {
    float len = glm::length(v);
    if (len > 0.00001f)
        return glm::normalize(v);
    return Vector(0.0f);
}

inline float Length(const Vector& v) {
    return glm::length(v);
}

inline Vector CrossProduct(const Vector& v1, const Vector& v2) {
    return glm::cross(v1, v2);
}

inline float DotProduct(const Vector& v1, const Vector& v2) {
    return glm::dot(v1, v2);
}

inline Vector RotateVector(Vector v, Axis axis, float angle_degrees) {
    float radians = glm::radians(angle_degrees);
    if (axis == X)
        return glm::rotateX(v, radians);
    if (axis == Y)
        return glm::rotateY(v, radians);
    if (axis == Z)
        return glm::rotateZ(v, radians);
    return v;
}

#endif // VECTOR_HPP_INCLUDED
