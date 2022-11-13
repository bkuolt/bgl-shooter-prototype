#ifndef FRUSTUM_H
#define FRUSTUM_H

class Frustum {
private:
  Planes planes[6];

public:
  bool intersects(const AABB &aabb) const {
    for (auto i = 0; i < 6; ++i) {
      for (auto j = 0; j < 8; ++j) {
        if (planes[i].contains(aabb[j])) {
          return true;
        }
      }
    }
    return false;
  }
};
#endif // FRUSTUM_H
