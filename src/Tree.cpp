#include "BSP.h"
#include <bitset>
#include <utility>
#include <vector>


std::vector<int32_t> clusters_leafs[100000];

/**
 * @brief Sucht alle Blätter,die zu einem Cluster gehören
 */
void AssignLeafesToCluster(void) {
  for (size_t i = 0; i < leafs.size(); ++i)
    clusters_leafs[leafs[i].cluster].push_back(i);
}

/**
 * @brief �bepr�ft,ob Punkt vor Ebene Liegt
 */
bool IsFrontFacing(size_t plane, vec3_t v) {
  size_t i = plane;

  return (planes[i].normal[X] * v[X] + planes[i].normal[Y] * v[Y] +
          planes[i].normal[Z] * v[Z] - planes[i].dist) >= 0;
}

/**
 * @brief Sucht Blatt des angegebenen Punktes
 */
std::pair<int32_t, int32_t> FindLeaf(vec3_t v) {
  int child = 0;
  int node = 0;

  while (child >= 0) {
    node = child;

    // Geht in Kindsknoten
    if (IsFrontFacing(nodes[node].planenum, v))
      child = nodes[node].children[0];
    else
      child = nodes[node].children[1];
  }

  // Gibt Knoten und Blatt zurück
  return std::make_pair(node, -child - 1);
}

/**
 * @brief Rendert alle Polygone im Cluster
 */
void RenderCluster(int32_t i) {
  size_t l;

  for (size_t j = 0; j < clusters_leafs[i].size();
       ++j) // alle Bl�tter des Cluster
  {
    l = clusters_leafs[i][j];                          // aktuelles Blatt
    for (size_t k = 0; k < leafs[l].numleaffaces; ++k) // alle Faces
      RenderFace(leaf_face[leafs[l].firstleafface + k]);
  }
}

/**
 * @brief NUR ZUM TEST: Rendert alle Cluster
 */
void RenderAllClusters(void) {
  for (size_t i = 0; i < vis->numclusters; ++i)
    RenderCluster(i);
}

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

typedef std::vector<bool> PVS;

/*
=====================================================================
Dekomprimiert ein PVS
=====================================================================*/
PVS DecompressPVS(const char *data, size_t num_clusters) {
  std::vector<bool> pvs;

  // (1) reserviert Speicher
  pvs.resize(num_clusters, false);

  // (2) Dekomprimiert Daten
  for (size_t c = 0, b = 0; c < num_clusters; b++) {
    if (data[b] == 0) {
      b++;
      c += data[b] * 8;
    } else {
      // Liest Byte in Bitset
      std::bitset<8> byte(data[b]);

      // Liest alle Bits
      for (size_t i = 0; i < 8; ++i)
        pvs[c + i] = byte[i];
      c += 8;
    }
  }

  // (3) gibt Daten zurück
  return pvs;
}

/*
=====================================================================
Dekomprimiert alle PVSs
=====================================================================*/
std::vector<PVS> DecompressPVS(dvis_t *vis) {
  std::vector<PVS> pvs;
  std::vector<int> offsets;
  int num_clusters;
  char *data;

  // (1) Reserviert Speicher
  num_clusters = vis->numclusters;
  pvs.resize(num_clusters);
  offsets.resize(num_clusters);

  // (2) setzt Zeiger
  data = reinterpret_cast<char *>(vis);

  // (3) berechnet Offsets
  for (size_t i = 0; i < num_clusters; ++i)
    offsets[i] = vis->bitofs[i][0];

  // (4) Decomprimiert alle PVSs
  for (size_t i = 0; i < num_clusters; ++i)
    pvs[i] = DecompressPVS(data + offsets[i], num_clusters);

  return pvs;
}

/*
=====================================================================
Dekomprimiert alle PVSs (Schnittstelle)
=====================================================================*/
void DecompressPVS(void) {
  std::vector<PVS> pvs = DecompressPVS(vis);

  // Reserviert Speicher
  clusters.resize(vis->numclusters);
  for (size_t i = 0; i < vis->numclusters; ++i)
    clusters[i] = pvs[i];
}

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------

size_t CountVisibleClusters(int cluster) {
  size_t count = 0;
  if (cluster >= 0)
    for (size_t i = 0; i < clusters[cluster].size(); ++i)
      if (clusters[cluster][i] == true)
        ++count;

  return count;
}

void DrawAllPVSFromCluster(size_t cluster) {
  // schaut potentiell sichtabre Cluster anch und zeichnet sie
  for (size_t i = 0; i < clusters.size(); ++i)
    if (clusters[cluster][i])
      RenderCluster(i);
}

/*
==================================================
=                  Kernst�ck                     =
==================================================*/
void DrawVisibleClusters(vec3_t v) {

  std::pair<int32_t, int32_t> tree;
  int32_t leaf;
  int32_t cluster;

  // (1) Sucht Blatt
  tree = FindLeaf(v);
  leaf = tree.second;

  // (2) Cluster in dem sich das Blatt befindet
  cluster = leafs[leaf].cluster;

  if (cluster == -1)
    RenderBSP();
  // RenderAllClusters();

  else {
    // schaut potentiell sichtabre Cluster anch und zeichnet sie
    for (size_t i = 0; i < clusters.size(); ++i)
      if (clusters[cluster][i])
        RenderCluster(i);
  }
}
