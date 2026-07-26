#include "bsp.hpp"
#include "config.hpp"

#define ILUT_USE_OPENGL
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include <spdlog/spdlog.h>

void AdaptCoordinateSystem(void);
void DecompressPVS(void);
void LoadLightmaps(void);
std::string GetDataPath(const std::string& folder);

FILE* file = nullptr;
dheader_t header;

std::vector<dvertex_t> vertices;
std::vector<dface_t> faces;
std::vector<dedge_t> edges;
std::vector<int32_t> face_edges;
std::vector<dnode_t> nodes;
std::vector<dleaf_t> leafs;
std::vector<texinfo_t> texinfos;
std::vector<dplane_t> planes;
std::vector<int16_t> leaf_face;
std::vector<char> lights;
std::vector<dbrush_t> brushes;
std::vector<dbrushside_t> brush_sides;
std::vector<unsigned short> leaf_brushes;
std::vector<dmodel_t> models;

weapon_t weapon;
bool detect_collisions = true;
static std::vector<char> vis_buffer;
dvis_t* vis = nullptr;

std::vector<GLuint> textures;
std::vector<std::vector<bool>> clusters;
std::vector<GLuint> lightmaps;
Sound gun;
Sound music;
bool render_lightmap_only = false;
Skybox skybox;

void LoadBSP(const char* filename) {
    if (!textures.empty()) {
        glDeleteTextures(static_cast<GLsizei>(textures.size()), textures.data());
        textures.clear();
    }
    if (!lightmaps.empty()) {
        glDeleteTextures(static_cast<GLsizei>(lightmaps.size()), lightmaps.data());
        lightmaps.clear();
    }

    spdlog::info("Opening {}...", GetConfigurationString(Level));
    file = std::fopen(filename, "rb");
    if (!file)
        return;

    if (std::fread(&header, sizeof(dheader_t), 1, file) != 1) {
        spdlog::error("Failed to read BSP header");
        return;
    }

    spdlog::info("  Initializing DevIL...");
    ilInit();
    iluInit();
    ilutInit();
    ilutRenderer(ILUT_OPENGL);
    ilEnable(IL_FILE_OVERWRITE);
    ilutEnable(ILUT_OPENGL_CONV);
    iluImageParameter(ILU_FILTER, ILU_BILINEAR);

    spdlog::info("  Reading Lumps...");
    vertices = LoadLumpArray<dvertex_t>(LUMP_VERTEXES);
    edges = LoadLumpArray<dedge_t>(LUMP_EDGES);
    faces = LoadLumpArray<dface_t>(LUMP_FACES);
    face_edges = LoadLumpArray<int32_t>(LUMP_SURFEDGES);
    nodes = LoadLumpArray<dnode_t>(LUMP_NODES);
    leafs = LoadLumpArray<dleaf_t>(LUMP_LEAFS);
    planes = LoadLumpArray<dplane_t>(LUMP_PLANES);
    texinfos = LoadLumpArray<texinfo_t>(LUMP_TEXINFO);
    leaf_face = LoadLumpArray<int16_t>(LUMP_LEAFFACES);
    lights = LoadLumpArray<char>(LUMP_LIGHTING);
    brushes = LoadLumpArray<dbrush_t>(LUMP_BRUSHES);
    brush_sides = LoadLumpArray<dbrushside_t>(LUMP_BRUSHSIDES);
    leaf_brushes = LoadLumpArray<unsigned short>(LUMP_LEAFBRUSHES);
    models = LoadLumpArray<dmodel_t>(LUMP_MODELS);

    spdlog::info("  Loading PVS...");
    vis_buffer.resize(header.lumps[LUMP_VISIBILITY].filelen);
    vis = reinterpret_cast<dvis_t*>(vis_buffer.data());
    std::fseek(file, header.lumps[LUMP_VISIBILITY].fileofs, SEEK_SET);
    if (std::fread(vis, header.lumps[LUMP_VISIBILITY].filelen, 1, file) != 1 && header.lumps[LUMP_VISIBILITY].filelen > 0) {
        spdlog::warn("PVS fread warning or empty PVS");
    }

    CD::CreateClusters(vis);
    AssignLeafesToCluster();

    spdlog::info("  Creating Lightmaps...");
    LoadLightmaps();

    if (GetConfigurationInt(DrawTextures)) {
        spdlog::info("  Loading Textures...");
        LoadTextures();
    }

    if (GetConfigurationInt(DrawSkybox))
        skybox.load((GetConfigurationString(DataPath) + "sky.tga").c_str());

    spdlog::info("  Adapting Coordinate System...");
    AdaptCoordinateSystem();

    CreateAABBs();

    std::fclose(file);
    file = nullptr;

    spdlog::info("  Statistics:");
    spdlog::info("    Polygons : {}", faces.size());
    spdlog::info("    Vertices : {}", vertices.size());
    spdlog::info("    Brushes  : {}", brushes.size());
    spdlog::info("    Planes   : {}", planes.size());
    spdlog::info("    Textures : {}", textures.size());
    spdlog::info("    Nodes    : {}", nodes.size());
    spdlog::info("    Leaves   : {}", leafs.size());
    spdlog::info("    Clusters : {}", vis->numclusters);
    spdlog::info("  Initializing Window...");

    ilShutDown();
}

bool LoadTextures(void) {
    char name[200];
    size_t j;

    textures.resize(texinfos.size(), 0);

    if (!render_lightmap_only) {
        for (size_t i = 0; i < texinfos.size(); ++i) {
            std::strcpy(name, GetConfigurationString(DataPath).c_str());
            std::strcat(name, "textures/");
            std::strcat(name, texinfos[i].texture);
            std::strcat(name, GetConfigurationString(TextureFormat).c_str());

            for (j = 0; j < i; ++j) {
                if (std::string(texinfos[j].texture) == std::string(texinfos[i].texture))
                    break;
            }

            if (j == i) {
                spdlog::info("Loading texture: {}", name);
                textures[i] = ilutGLLoadImage(name);
                if (textures[i] == 0) {
                    spdlog::warn("Failed to load texture '{}'", name);
                } else {
                    glBindTexture(GL_TEXTURE_2D, textures[i]);
                    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, GetConfigurationInt(AnisotropicFilter));
                    glBindTexture(GL_TEXTURE_2D, 0);
                }
            } else {
                textures[i] = textures[j];
            }
        }
    }
    return true;
}

void LoadLightmaps(void) {
    ILuint id;
    lightmaps.resize(faces.size(), 0);

    for (size_t i = 1; i < faces.size(); ++i) {
        ilBindImage(id = CreateLightmap(i));
        lightmaps[i] = ilutGLBindTexImage();

        glBindTexture(GL_TEXTURE_2D, lightmaps[i]);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, GetConfigurationInt(AnisotropicFilter));
        glBindTexture(GL_TEXTURE_2D, 0);

        ilDeleteImage(id);
    }
}

void SwapAxis(vec3_t v) {
    float temp = v[Y];
    v[Y] = v[Z];
    v[Z] = -temp;
}

void SwapAxis(short v[3]) {
    short temp = v[Y];
    v[Y] = v[Z];
    v[Z] = -temp;
}

void SwapAxis(Vector& v) {
    float temp = v[Y];
    v[Y] = v[Z];
    v[Z] = -temp;
}

void AdaptCoordinateSystem(void) {
    size_t i;
    for (i = 0; i < vertices.size(); ++i)
        SwapAxis(vertices[i].point);
    for (i = 0; i < texinfos.size(); ++i) {
        SwapAxis(texinfos[i].vecs[0]);
        SwapAxis(texinfos[i].vecs[1]);
    }
    for (i = 0; i < planes.size(); ++i)
        SwapAxis(planes[i].normal);
    for (i = 0; i < leafs.size(); ++i) {
        SwapAxis(leafs[i].mins);
        SwapAxis(leafs[i].maxs);
    }
    for (i = 0; i < models.size(); ++i) {
        SwapAxis(models[i].mins);
        SwapAxis(models[i].maxs);
    }
}
