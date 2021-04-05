#include "Windows.h"
#include "IL/ILU.h"
#include "GLEe.h"
#include "Bsp.h"
#include <cmath>
#include <algorithm>
#include "IL/IL.h"
#include "IL/ILU.h"

#include <cstring>
#include <cstdlib>


#define U 0
#define V 1

uint32_t GetVertex(uint32_t face, uint32_t i) {
    int edge;
    int vertex = 0;

    // Ecke berechnen
    edge = face_edges[faces[face].firstedge + i];

    // Vertex berechnen
    if (edge < 0) {
        vertex = edges[-edge].v[0];
    } else {
        vertex = edges[edge].v[1];
    }

    // Vertex zurückgeben
    return vertex;
}

std::pair<float, float> GetTexCoordinate(uint32_t texture,uint32_t vertex) {
    float uv[2];

    // Texturkoordinaten festlegen
    for (size_t i = 0; i < 2; ++i) {
      uv[i] = vertices[vertex].point[X] * texinfos[texture].vecs[i][X]  +
              vertices[vertex].point[Y] * texinfos[texture].vecs[i][Y]  +
              vertices[vertex].point[Z] * texinfos[texture].vecs[i][Z]  +
                                          texinfos[texture].vecs[i][3];
    }
    return std::make_pair(uv[0], uv[1]);
}

struct Lightmap {
    int width;
    int height;
    char data[16*16*3*30];
};

/**
 * @brief Erstellt Lightmap für ein Face
 */
unsigned int CreateLightmap(uint32_t index) {
	uint32_t t;
	uint32_t vert;
    float min[2];
    float max[2] = {0, 0};
    float u[100];
    float v[100];
    char name[100];
    int width, height;
    Lightmap lightmap;

	// Texturindex berechnen
	t = faces[index].texinfo;

	// Berechnet alle texturkoordinaten
	for(size_t i = 0; i < faces[index].numedges; ++i) {
	    vert = GetVertex(index, i);
	    u[i] = GetTexCoordinate(t, vert).first;
	    v[i] = GetTexCoordinate(t, vert).second;
	}

    max[U] = *std::max_element(u, u + faces[index].numedges);
    max[V] = *std::max_element(v, v + faces[index].numedges);
    min[U] = *std::min_element(u, u + faces[index].numedges);
    min[V] = *std::min_element(v, v + faces[index].numedges);

	// (3) Berechnet Maße
	 width = (ceil(max[U] / 16.0) - floor(min[U] / 16.0)) + 1;
	height = (ceil(max[V] / 16.0) - floor(min[V] / 16.0)) + 1;

	// (5) speichert Maße
	lightmap.width  = width;
	lightmap.height = height;

	// (6) Kopiert Daten in Lightmapstruktur
	std::copy(lights.begin() + faces[index].lightofs,
              lights.begin() + faces[index].lightofs + width * height *3,
              lightmap.data);

    ILuint id;

    ilBindImage(id = ilGenImage());
    ilTexImage(width, height, 0, 3, GL_RGB, GL_UNSIGNED_BYTE, lightmap.data);
    return id;
}

void SetLightmapCoordinates(uint32_t face, float tex_u, float tex_v) {
    uint32_t index = face;
	uint32_t t;
	uint32_t vert;
    float min[2];
    float max[2] = {0, 0};
    float u[100];
    float v[100];
    int width, height;
    Lightmap lightmap;

	// Texturindex berechnen
	t = faces[index].texinfo;

	// Berechnet alle texturkoordinaten
	for (size_t i = 0; i < faces[index].numedges; ++i) {
	    vert = GetVertex(index, i);
	    u[i] = GetTexCoordinate(t, vert).first;
	    v[i] = GetTexCoordinate(t, vert).second;
	}

    // Bestimmt Extrempunkte!
    max[U] = *std::max_element(u, u + faces[index].numedges);
    max[V] = *std::max_element(v, v + faces[index].numedges);
    min[U] = *std::min_element(u, u + faces[index].numedges);
    min[V] = *std::min_element(v, v + faces[index].numedges);

	// (3) Berechnet Maße
	 width = (ceil(max[U] / 16.0) - floor(min[U] / 16.0)) + 1;
	height = (ceil(max[V] / 16.0) - floor(min[V] / 16.0)) + 1;

    float MidPolyU = (min[U] + max[U]) / 2.0;
    float MidPolyV = (min[V] + max[V]) / 2.0;
    float MidTexU = width / 2.0;
    float MidTexV = height / 2.0;
    float lightmap_u = MidTexU + (tex_u - MidPolyU) / 16.0;
    float lightmap_v = MidTexV + (tex_v - MidPolyV) / 16.0;

    // Basistexturkoordinaten
    glMultiTexCoord2f(GL_TEXTURE0, lightmap_u / width, lightmap_v / height);
    // Lightmapkoordinaten
    glMultiTexCoord2f(GL_TEXTURE1, lightmap_u / width, lightmap_v / height);
}
