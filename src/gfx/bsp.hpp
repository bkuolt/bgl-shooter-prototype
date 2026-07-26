#ifndef BSP_HPP_INCLUDED
#define BSP_HPP_INCLUDED

#include "bounding_box.hpp"
#include "md2.hpp"
#include "skybox.hpp"
#include "sound.hpp"
#include "types.hpp"
#include <GL/freeglut.h>
#include <GL/glew.h>
#define ILUT_USE_OPENGL
#include "ilut_compat.hpp"
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include <cstdint>
#include <cstdio>
#include <utility>
#include <vector>

#define __DEBUG__

extern weapon_t weapon;
extern Skybox skybox;

// Quake II BSP Data Structures
extern dheader_t header;

extern std::vector<dvertex_t> vertices;
extern std::vector<dface_t> faces;
extern std::vector<dedge_t> edges;
extern std::vector<int32_t> face_edges;
extern std::vector<dnode_t> nodes;
extern std::vector<dleaf_t> leafs;
extern std::vector<texinfo_t> texinfos;
extern std::vector<dplane_t> planes;
extern std::vector<int16_t> leaf_face;
extern std::vector<char> lights;
extern std::vector<dbrush_t> brushes;
extern std::vector<dbrushside_t> brush_sides;
extern std::vector<unsigned short> leaf_brushes;
extern std::vector<dmodel_t> models;
extern dvis_t* vis;

// Internal
extern std::vector<GLuint> textures;
extern std::vector<std::vector<bool>> clusters;
extern std::vector<GLuint> lightmaps;

extern FILE* file;
extern Sound gun;
extern Sound music;
extern bool detect_collisions;

template <typename T> std::vector<T> LoadLumpArray(size_t lump) {
    size_t count = header.lumps[lump].filelen / sizeof(T);
    size_t offset = header.lumps[lump].fileofs;
    std::vector<T> array(count);

    if (file != nullptr && count > 0) {
        std::fseek(file, offset, SEEK_SET);
        size_t read_bytes = std::fread(&array.front(), sizeof(T), count, file);
        (void)read_bytes;
    }
    return array;
}

// Rendering
void RenderVisibleModels(void);
void RenderWater(void);
void RenderFace(size_t i);
void RenderBSP(void);
void RenderModel(int32_t);
void SetLightmapCoordinates(uint32_t face, float tex_u, float tex_v);

// Data Management
void LoadBSP(const char* filename);
bool LoadTextures(void);
unsigned int CreateLightmap(uint32_t);
void SwapAxis(vec3_t v);
void SwapAxis(short v[3]);
void SwapAxis(Vector& v);

// Collision & Visibility
void RenderCluster(int32_t i);
void RenderAllClusters(void);
void DrawVisibleClusters(vec3_t v);
void CreateAABBs(void);
void AssignLeafesToCluster(void);
std::pair<int32_t, int32_t> FindLeaf(vec3_t v);

namespace CD {
void CreateClusters(dvis_t* vis);
std::pair<int32_t, int32_t> FindNodeLeaf(vec3_t v);
void RenderVisibleClusters(void);
const char* GetVisibiltyString(void);
const char* GetCollisionDetetctionString(void);
bool WouldHaveWallCollision(const Vector& v);
} // namespace CD

bool DoCollide(int32_t cluster);
bool WouldHaveWallCollision(const Vector& v);

#endif // BSP_HPP_INCLUDED
