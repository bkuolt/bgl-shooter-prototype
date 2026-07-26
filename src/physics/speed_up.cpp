#include "speed_up.hpp"
#include <vector>

std::vector<AABB> aabbs;

void CreateAABBs(void) {
    aabbs.clear();
    aabbs.reserve(leafs.size());

    for (size_t i = 0; i < leafs.size(); ++i) {
        Vector min(leafs[i].mins[0], leafs[i].mins[1], leafs[i].mins[2]);
        Vector max(leafs[i].maxs[0], leafs[i].maxs[1], leafs[i].maxs[2]);

        SwapAxis(min);
        SwapAxis(max);

        aabbs.emplace_back(min, max);
    }
}
