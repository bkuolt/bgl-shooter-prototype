#ifndef BSP_H_INCLUDED
#define BSP_H_INCLUDED

#include "Windows.h"
#include "GLEE.h"
#include "Header.h"

#include <GL/GL.h>
#include <vector>
#include <ctime>
#include <cstdio>
#include <cstdint>
#include "BoundingBox.h"
#include "MD2.h"
#include "Skybox.h"
#include "Sound.h"

/*
==============================================================
=                                                            =
=                     Build Options                          =
=                                                            =
==============================================================*/
#define __DEBUG__

extern Weapon weapon;
extern Skybox skybox;

/*
=====================================================================
=                                                                   =
=                           Variablen                               =
=                                                                   =
=====================================================================*/
//  Quake II
extern dheader_t header;

extern std::vector<dvertex_t> vertices;
extern std::vector<dface_t>   faces;
extern std::vector<dedge_t>   edges;
extern std::vector<int32_t>   face_edges;
extern std::vector<dnode_t>   nodes;
extern std::vector<dleaf_t>   leafs;
extern std::vector<texinfo_t> texinfos;
extern std::vector<dplane_t>  planes;
extern std::vector<int16_t>   leaf_face;
extern std::vector<char>           lights;
extern std::vector<dbrush_t>       brushes;
extern std::vector<dbrushside_t>   brush_sides;
extern std::vector<unsigned short> leaf_brushes;
extern std::vector<dmodel_t>       models;
extern dvis_t *vis;

// Intern
extern std::vector<GLuint> textures;
extern std::vector< std::vector<bool> > clusters;
extern std::vector<GLuint> lightmaps;

extern FILE * file;
extern Sound gun;
extern Sound music;
extern bool detect_collisions;

/*
=====================================================================
=                                                                   =
=                           Funktionen                              =
=                                                                   =
=====================================================================*/
inline int GetElapsedTime(void)
{
    return clock(); // Bug in GLUT v3.7.6!?
}

/*
==================================================
Liest Lump
==================================================*/
template<typename T>
std::vector<T> LoadLumpArray(size_t lump)
{
    size_t count  = header.lumps[lump].filelen / sizeof(T);
    size_t offset = header.lumps[lump].fileofs;
    std::vector<T> array(count);

    fseek(file,offset,SEEK_SET);
    fread(&array.front(),sizeof(T),count,file);
    return array;
}

/*
==================================================
Rendering
==================================================*/
void RenderVisibleModels(void);
void RenderWater(void);
void RenderFace(size_t i);
void RenderBSP(void); // alt?
void RenderModel(int32_t);
void SetLightmapCoordinates(uint32_t face,float tex_u,float tex_v);

/*
==================================================
Datenmanagement
==================================================*/
void LoadBSP(const char *filename);
bool LoadTextures(void);
unsigned int CreateLightmap(uint32_t);
void SwapAxis(vec3_t v);
void SwapAxis(short v[3]);

/*
==================================================
Kollisionserkennung
==================================================*/
void RenderCluster(int32_t i);
void RenderAllClusters(void);
void DrawVisibleClusters(vec3_t v);
void CreateAABBs(void);
void AssignLeafesToCluster(void); // alt?
std::pair<int32_t,int32_t> FindLeaf(vec3_t v);

namespace CD {
    void CreateClusters(dvis_t *vis);
    std::pair<int32_t,int32_t> FindNodeLeaf(vec3_t v);
    void RenderVisibleClusters(void);
    const char* GetVisibiltyString(void);
    const char* GetCollisionDetetctionString(void);
}

bool DoCollide(int32_t cluster);
bool WouldHaveWallCollision(const Vector &v);
#endif
