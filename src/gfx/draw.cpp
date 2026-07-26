#include "bsp.hpp"
#include "config.hpp"
#include <GL/glew.h>
#include <IL/il.h>
#include <IL/ilut.h>

inline void RenderFace(size_t i, int flags) {
    size_t vertex;
    int edge;
    size_t texture;
    float uv[2];

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    texture = faces[i].texinfo;

    if (texinfos[faces[i].texinfo].flags & SURF_WARP) {
        if (!GetConfigurationInt(DrawWater)) {
            return;
        } else if (!(flags & SURF_WARP) && GetConfigurationInt(AnimateWater)) {
            return;
        }
    }

    if (texinfos[texture].flags & SURF_NODRAW) {
        return;
    } else if (GetConfigurationInt(DrawSkybox) && (texinfos[texture].flags & SURF_SKY)) {
        return;
    }

    glPushAttrib(GL_TEXTURE_BIT);

    glActiveTexture(GL_TEXTURE1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, lightmaps[i]);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glActiveTexture(GL_TEXTURE0);
    if (GetConfigurationInt(DrawTextures)) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textures[texture]);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    }

    glBegin(GL_TRIANGLE_FAN);
    for (size_t j = 0; j < faces[i].numedges; ++j) {
        edge = face_edges[faces[i].firstedge + j];
        if (edge < 0) {
            vertex = edges[-edge].v[0];
        } else {
            vertex = edges[edge].v[1];
        }

        for (size_t c = 0; c < 2; ++c) {
            uv[c] = vertices[vertex].point[X] * texinfos[texture].vecs[c][X] +
                    vertices[vertex].point[Y] * texinfos[texture].vecs[c][Y] +
                    vertices[vertex].point[Z] * texinfos[texture].vecs[c][Z] + texinfos[texture].vecs[c][3];
        }

        SetLightmapCoordinates(i, uv[0], uv[1]);
        glNormal3fv(planes[faces[i].planenum].normal);
        glVertex3fv(vertices[vertex].point);
    }
    glEnd();

    glActiveTexture(GL_TEXTURE0);
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glPopAttrib();
}

void RenderFace(size_t i) {
    RenderFace(i, 0x00000000);
}

void RenderBSP(void) {
    RenderAllClusters();
}

void RenderModel(int32_t i) {
    for (size_t j = 0; j < models[i].numfaces; ++j) {
        RenderFace(models[i].firstface + j);
    }
}

void RenderVisibleModels(void) {
    for (size_t i = 1; i < models.size(); ++i) {
        RenderModel(i);
    }
}

void RenderWater(void) {
    static GLuint list = 0;
    static double k = 0;
    static int last = GetElapsedTime();

    if (list == 0) {
        list = glGenLists(1);
        glNewList(list, GL_COMPILE);
        for (size_t i = 0; i < faces.size(); ++i) {
            if (texinfos[faces[i].texinfo].flags & SURF_WARP) {
                RenderFace(i, SURF_WARP);
            }
        }
        glEndList();
    } else {
        if (last + 10 <= GetElapsedTime()) {
            k += 1;
            last = GetElapsedTime();
        }

        glMatrixMode(GL_TEXTURE);
        glRotated(k, 0.0, 0.0, 1.0);
        glCallList(list);
    }
}
