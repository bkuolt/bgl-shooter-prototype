#include "Windows.h"
#include "GLEE.h"
#include "BSP.h"
#include <IL/IL.h>
#include <IL/ILUT.h>
#include "Config.h"

/*
=========================================================
Rendert Polygon (Flags als Info)
=========================================================*/
inline void RenderFace(size_t i,int flags)
{
    size_t vertex;
    int edge;
    size_t texture;
    float uv[2];

    glColor4f(1,1,1,1);
    texture = faces[i].texinfo;

    //===============================================
    // Überprüft,ob Wasser animiert werden soll
    //===============================================
    if(texinfos[faces[i].texinfo].flags & SURF_WARP) // Wasseroberfläche
        if(!GetConfigurationInt(DrawWater)) // Wasser überhaupt zeichnen
            return;
        else
            if(!(flags & SURF_WARP) && // Flag ist keine Wasseoberfläche
                GetConfigurationInt(AnimateWater))
                return;

    //===============================================
    // Zeichnet keine Trigger und sonstige ein!
    //===============================================
    if(texinfos[texture].flags & SURF_NODRAW)
        return;
    if(GetConfigurationInt(DrawSkybox) && texinfos[texture].flags & SURF_SKY)
        return;

    glPushAttrib(GL_TEXTURE_BIT);
    // Lightmap setzen
    glActiveTexture(GL_TEXTURE1);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,lightmaps[i]); // textures[texture]
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    //  Basistextur setzen
    glActiveTexture(GL_TEXTURE0);
        // Überprüft,ob texturiert werden soll
       if(GetConfigurationInt(DrawTextures))
       {
           glEnable(GL_TEXTURE_2D);
           glBindTexture(GL_TEXTURE_2D,textures[texture]);
           glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,  GL_MODULATE);
       }

    glBegin(GL_TRIANGLE_FAN);
        for(size_t j = 0;j < faces[i].numedges;++j)
        {
            edge = face_edges[faces[i].firstedge + j];
            // Vertex festlegen
            if(edge < 0)
                vertex = edges[-edge].v[0];
            else
                vertex = edges[edge].v[1];

            // Texturkoordinaten festlegen
            for(size_t i = 0;i < 2;++i)
              uv[i] = vertices[vertex].point[X] * texinfos[texture].vecs[i][X]  +
                      vertices[vertex].point[Y] * texinfos[texture].vecs[i][Y]  +
                      vertices[vertex].point[Z] * texinfos[texture].vecs[i][Z]  +
                                                  texinfos[texture].vecs[i][3];
            // Setzt Basistextur- und Lightmapkoordinaten
            SetLightmapCoordinates(i,uv[0],uv[1]);

            // Normale
            glNormal3fv(planes[faces[i].planenum].normal);
            // Vertex festlegen
            glVertex3fv(vertices[vertex].point);
        }
    glEnd();

    glActiveTexture(GL_TEXTURE0);
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,0);
    glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,0);
        glDisable(GL_TEXTURE_2D);
    glPopAttrib();
}


void RenderFace(size_t i)
{
    RenderFace(i,0x00000000); // keine Flags
}

/*
==================================================
Rendert den gesamten BSP erstellt Displayliste
==================================================*/
void RenderBSP(void)
{
    RenderAllClusters();
}

/*
==================================================
Rendert den gesamten BSP erstellt Displayliste
==================================================*/
void RenderModel(int32_t i)
{
    for(size_t j = 0;j < models[i].numfaces;++j)
        RenderFace(models[i].firstface + j);
}

/*
=========================================================
Rendert Animiertes Wasser
=========================================================*/
void RenderWater(void)
{
    static GLuint list = 0;
    static double k = 0;
    static int last = GetElapsedTime();

    if(list == 0)
    {
        list = glGenLists(1);
        glNewList(list,GL_COMPILE);
            for(size_t i = 0;i < faces.size();++i)
                if(texinfos[faces[i].texinfo].flags & SURF_WARP)
                    RenderFace(i,SURF_WARP);
        glEndList();
    }
    else
    {
        if(last + 10 <= GetElapsedTime()){
            k+= 1;
            last = GetElapsedTime();
        }

        glMatrixMode(GL_TEXTURE);
        glRotated(k,0.0,0,1);
        glCallList(list);
    }
}
