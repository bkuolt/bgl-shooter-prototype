#include "bsp.hpp"
#include <bitset>
#include <utility>
#include <vector>

std::vector<int32_t> clusters_leafs[100000];

void AssignLeafesToCluster(void) {
    for (size_t i = 0; i < leafs.size(); ++i) {
        if (leafs[i].cluster >= 0 && static_cast<size_t>(leafs[i].cluster) < 100000) {
            clusters_leafs[leafs[i].cluster].push_back(i);
        }
    }
}

bool IsFrontFacing(size_t plane, vec3_t v) {
    size_t i = plane;
    return (planes[i].normal[X] * v[X] + planes[i].normal[Y] * v[Y] + planes[i].normal[Z] * v[Z] - planes[i].dist) >= 0;
}

std::pair<int32_t, int32_t> FindLeaf(vec3_t v) {
    int child = 0;
    int node = 0;

    while (child >= 0) {
        node = child;
        if (IsFrontFacing(nodes[node].planenum, v))
            child = nodes[node].children[0];
        else
            child = nodes[node].children[1];
    }
    return std::make_pair(node, -child - 1);
}

void RenderCluster(int32_t i) {
    size_t l;
    for (size_t j = 0; j < clusters_leafs[i].size(); ++j) {
        l = clusters_leafs[i][j];
        for (size_t k = 0; k < leafs[l].numleaffaces; ++k)
            RenderFace(leaf_face[leafs[l].firstleafface + k]);
    }
}

void RenderAllClusters(void) {
    for (size_t i = 0; i < vis->numclusters; ++i)
        RenderCluster(i);
}

typedef std::vector<bool> PVS;

PVS DecompressPVS(const char* data, size_t num_clusters) {
    std::vector<bool> pvs(num_clusters, false);

    for (size_t c = 0, b = 0; c < num_clusters; b++) {
        if (data[b] == 0) {
            b++;
            c += data[b] * 8;
        } else {
            std::bitset<8> byte(data[b]);
            for (size_t i = 0; i < 8; ++i)
                pvs[c + i] = byte[i];
            c += 8;
        }
    }
    return pvs;
}

std::vector<PVS> DecompressPVS(dvis_t* vis) {
    int num_clusters = vis->numclusters;
    std::vector<PVS> pvs(num_clusters);
    std::vector<int> offsets(num_clusters);

    char* data = reinterpret_cast<char*>(vis);

    for (size_t i = 0; i < static_cast<size_t>(num_clusters); ++i)
        offsets[i] = vis->bitofs[i][0];

    for (size_t i = 0; i < static_cast<size_t>(num_clusters); ++i)
        pvs[i] = DecompressPVS(data + offsets[i], num_clusters);

    return pvs;
}

void DecompressPVS(void) {
    std::vector<PVS> pvs = DecompressPVS(vis);
    clusters.resize(vis->numclusters);
    for (size_t i = 0; i < static_cast<size_t>(vis->numclusters); ++i)
        clusters[i] = pvs[i];
}

size_t CountVisibleClusters(int cluster) {
    size_t count = 0;
    if (cluster >= 0)
        for (size_t i = 0; i < clusters[cluster].size(); ++i)
            if (clusters[cluster][i])
                ++count;
    return count;
}

void DrawAllPVSFromCluster(size_t cluster) {
    for (size_t i = 0; i < clusters.size(); ++i)
        if (clusters[cluster][i])
            RenderCluster(i);
}

void DrawVisibleClusters(vec3_t v) {
    std::pair<int32_t, int32_t> tree = FindLeaf(v);
    int32_t leaf = tree.second;
    int32_t cluster = leafs[leaf].cluster;

    if (cluster == -1)
        RenderBSP();
    else {
        for (size_t i = 0; i < clusters.size(); ++i)
            if (clusters[cluster][i])
                RenderCluster(i);
    }
}
