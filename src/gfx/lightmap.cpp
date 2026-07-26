#include "bsp.hpp"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <utility>

#define U 0
#define V 1

uint32_t GetVertex(uint32_t face, uint32_t i) {
    int edge = face_edges[faces[face].firstedge + i];
    int vertex = (edge < 0) ? edges[-edge].v[0] : edges[edge].v[1];
    return vertex;
}

std::pair<float, float> GetTexCoordinate(uint32_t texture, uint32_t vertex) {
    float uv[2];
    for (size_t i = 0; i < 2; ++i) {
        uv[i] = vertices[vertex].point[X] * texinfos[texture].vecs[i][X] +
                vertices[vertex].point[Y] * texinfos[texture].vecs[i][Y] +
                vertices[vertex].point[Z] * texinfos[texture].vecs[i][Z] + texinfos[texture].vecs[i][3];
    }
    return std::make_pair(uv[0], uv[1]);
}

struct Lightmap {
    int width;
    int height;
    char data[16 * 16 * 3 * 30];
};

unsigned int CreateLightmap(uint32_t index) {
    uint32_t t = faces[index].texinfo;
    uint32_t vert;
    float min[2];
    float max[2] = {0, 0};
    float u[100];
    float v[100];
    int width, height;
    Lightmap lightmap;

    for (size_t i = 0; i < faces[index].numedges; ++i) {
        vert = GetVertex(index, i);
        u[i] = GetTexCoordinate(t, vert).first;
        v[i] = GetTexCoordinate(t, vert).second;
    }

    max[U] = *std::max_element(u, u + faces[index].numedges);
    max[V] = *std::max_element(v, v + faces[index].numedges);
    min[U] = *std::min_element(u, u + faces[index].numedges);
    min[V] = *std::min_element(v, v + faces[index].numedges);

    width = (std::ceil(max[U] / 16.0f) - std::floor(min[U] / 16.0f)) + 1;
    height = (std::ceil(max[V] / 16.0f) - std::floor(min[V] / 16.0f)) + 1;

    lightmap.width = width;
    lightmap.height = height;

    if (faces[index].lightofs >= 0 &&
        static_cast<size_t>(faces[index].lightofs) + width * height * 3 <= lights.size()) {
        std::copy(lights.begin() + faces[index].lightofs, lights.begin() + faces[index].lightofs + width * height * 3,
                  lightmap.data);
    } else {
        std::memset(lightmap.data, 255, sizeof(lightmap.data));
    }

    ILuint id;
    ilBindImage(id = ilGenImage());
    ilTexImage(width, height, 0, 3, GL_RGB, GL_UNSIGNED_BYTE, lightmap.data);
    return id;
}

void SetLightmapCoordinates(uint32_t face, float tex_u, float tex_v) {
    uint32_t index = face;
    uint32_t t = faces[index].texinfo;
    uint32_t vert;
    float min[2];
    float max[2] = {0, 0};
    float u[100];
    float v[100];
    int width, height;

    for (size_t i = 0; i < faces[index].numedges; ++i) {
        vert = GetVertex(index, i);
        u[i] = GetTexCoordinate(t, vert).first;
        v[i] = GetTexCoordinate(t, vert).second;
    }

    max[U] = *std::max_element(u, u + faces[index].numedges);
    max[V] = *std::max_element(v, v + faces[index].numedges);
    min[U] = *std::min_element(u, u + faces[index].numedges);
    min[V] = *std::min_element(v, v + faces[index].numedges);

    width = (std::ceil(max[U] / 16.0f) - std::floor(min[U] / 16.0f)) + 1;
    height = (std::ceil(max[V] / 16.0f) - std::floor(min[V] / 16.0f)) + 1;

    float MidPolyU = (min[U] + max[U]) / 2.0f;
    float MidPolyV = (min[V] + max[V]) / 2.0f;
    float MidTexU = width / 2.0f;
    float MidTexV = height / 2.0f;
    float lightmap_u = MidTexU + (tex_u - MidPolyU) / 16.0f;
    float lightmap_v = MidTexV + (tex_v - MidPolyV) / 16.0f;

    glMultiTexCoord2f(GL_TEXTURE0, lightmap_u / width, lightmap_v / height);
    glMultiTexCoord2f(GL_TEXTURE1, lightmap_u / width, lightmap_v / height);
}
