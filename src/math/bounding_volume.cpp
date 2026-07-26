#include "bounding_box.hpp"
#include <memory>

/**
 * @brief Constructs the tightest enclosing Oriented Bounding Volume
 */
std::unique_ptr<OrientedBoundingVolume> CreateBoundingVolume(float width, float height, float depth, float radius) {
    return std::make_unique<OrientedBoundingVolume>(width, height, depth);
}

std::unique_ptr<OrientedBoundingVolume> CreateBoundingVolume(const float* vertices, size_t count) {
#ifdef __DEBUG__
    return std::make_unique<OrientedBoundingVolume>(vertices, count);
#else
    return nullptr;
#endif
}
