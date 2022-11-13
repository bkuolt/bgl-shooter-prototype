#include "Bsp.h"

AABB *aabbs = NULL;
GLuint lists;
extern Camera camera;

std::vector<std::vector<int32_t>> cluster_leafs;

/*
==================================================================
Erstellt AABBs sowie Displaylists f�r Bl�tter
==================================================================*/
void CreateAABBs(void) {
  aabbs = new AABB[faces.size() + models.size()];

  // erstellt AABBs
  printf("\tBerechnet AABBs fuer Frustum Culling\n");
  for (size_t i = 0; i < leafs.size(); ++i) {
    aabbs[i] =
        AABB(Vector(leafs[i].mins[X], leafs[i].mins[Y], leafs[i].mins[Z]),
             Vector(leafs[i].maxs[X], leafs[i].maxs[Y], leafs[i].maxs[Z]));
  }

  // erstellt DisplayListen
  lists = glGenLists(faces.size() + models.size());

  // f�llt Listen
  printf("\tErstellt Displaylisten  \n"); // TODO
  for (size_t i = 0; i < leafs.size(); ++i) {
    glNewList(lists + i, GL_COMPILE);
    for (size_t j = 0; j < leafs[i].numleaffaces; ++j)
      RenderFace(leaf_face[leafs[i].firstleafface + j]);
    glEndList();
  }

  ////////////////////////////////////////////////////
  // Genau das gleiche Prozeder f�r Modelle
  int offset = leafs.size();

  for (size_t i = 1; i < models.size(); ++i) {
    glNewList(lists + offset + i, GL_COMPILE);
    RenderModel(i);
    glEndList();
  }

  for (size_t i = 1; i < models.size(); ++i) {
    aabbs[i + offset] =
        AABB(Vector(models[i].mins[X], models[i].mins[Y], models[i].mins[Z]),
             Vector(models[i].maxs[X], models[i].maxs[Y], models[i].maxs[Z]));
  }
  ////////////////////////////////////////////////////

  // speichert alle Bl�tter eines Clusters
  cluster_leafs.resize(vis->numclusters);

  for (int32_t i = 0; i < leafs.size(); ++i)
    if (leafs[i].cluster != -1)
      cluster_leafs[leafs[i].cluster].push_back(i);
}

/*
==================================================================
Rendert alle Leafs,die sich im Frustum befinden
==================================================================*/
void RenderAABBs(void) {
  int count = 0;

  for (size_t i = 0; i < leafs.size(); ++i)
    if (camera.frustum.isWithin(aabbs[i]))
      glCallList(lists + i);
}

/*
==================================================================
Rendert alle Modelle,die sich im Frustum befinden
==================================================================*/
void RenderVisibleModels(void) {
  static const int offset = leafs.size();

  for (size_t i = 1; i < models.size(); ++i)
    if (camera.frustum.isWithin(aabbs[i + offset]))
      glCallList(lists + i + offset);
}

/*
==================================================================
Rendert alle Polygone der Bl�tter,die zu diesem Cluster geh�ren
==================================================================*/
void RenderCluster(int32_t c) {
  // Zeichnet nur Bl�tter,die im Frustum sind!
  for (size_t i = 0; i < cluster_leafs[c].size(); ++i)
    if (camera.frustum.isWithin(aabbs[cluster_leafs[c][i]]))
      glCallList(lists + cluster_leafs[c][i]);
}

void RenderAllClusters(void) {
  for (size_t i = 0; i < cluster_leafs.size(); ++i)
    RenderCluster(i);
}
