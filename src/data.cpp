#include "Windows.h"
#include "Glee.h"
#include "BSP.h"
#include <string>
#include <cctype>
#include "Config.h"

#include <IL/IL.h>
#include <IL/ILUT.h>

// Vorwärtsdeklarationen
void AdaptCoordinateSystem(void);
void DecompressPVS(void);
void LoadLightmaps(void);
std::string GetDataPath(const std::string &folder);

//  Quake II
FILE *file;
dheader_t header;

std::vector<dvertex_t> vertices;
std::vector<dface_t>   faces;
std::vector<dedge_t>   edges;
std::vector<int32_t>   face_edges;
std::vector<dnode_t>   nodes;
std::vector<dleaf_t>   leafs;
std::vector<texinfo_t> texinfos;
std::vector<dplane_t>  planes;
std::vector<int16_t>   leaf_face;
std::vector<char>      lights;
std::vector<dbrush_t>  brushes;
std::vector<dbrushside_t>   brush_sides;
std::vector<unsigned short> leaf_brushes;
std::vector<dmodel_t> models;


Weapon *current_weapon = false;
bool detect_collisions = true;
dvis_t *vis;

// intern
std::vector<GLuint>    textures;
std::vector< std::vector<bool> > clusters;
std::vector<GLuint>    lightmaps;
Sound gun;
Sound music;
bool render_lightmap_only = false;
Skybox skybox;


/*
==================================================
Lädt BSP
==================================================*/
void LoadBSP(const char *filename) {
    // (1) Öffnet Datei
    printf("\nOeffnet %s...\n", GetConfigurationString(Level).c_str());
    file = fopen(filename, "rb");
    fread(&header, sizeof(dheader_t), 1, file);

    // Startet DevIL
    printf("\tInitialisiert DevIL...\n");
    ilInit();
    iluInit();
    ilutInit();
    ilutRenderer(ILUT_OPENGL);
    ilEnable(IL_FILE_OVERWRITE);
    ilutEnable(ILUT_OPENGL_CONV);
    iluImageParameter(ILU_FILTER, ILU_BILINEAR);

    // (2) Lädt Lumps
    printf("\tLiest Lumps...\n");
    vertices     = LoadLumpArray<dvertex_t>(LUMP_VERTEXES);
    edges        = LoadLumpArray<dedge_t>  (LUMP_EDGES);
    faces        = LoadLumpArray<dface_t>  (LUMP_FACES);
    face_edges   = LoadLumpArray<int32_t>  (LUMP_SURFEDGES);
    nodes        = LoadLumpArray<dnode_t>  (LUMP_NODES);
    leafs        = LoadLumpArray<dleaf_t>  (LUMP_LEAFS);
    planes       = LoadLumpArray<dplane_t> (LUMP_PLANES);
    texinfos     = LoadLumpArray<texinfo_t>(LUMP_TEXINFO);
    leaf_face    = LoadLumpArray<int16_t>(LUMP_LEAFFACES);
    lights       = LoadLumpArray<char>(LUMP_LIGHTING);
    brushes      = LoadLumpArray<dbrush_t>(LUMP_BRUSHES);
    brush_sides  = LoadLumpArray<dbrushside_t>(LUMP_BRUSHSIDES);
    leaf_brushes = LoadLumpArray<unsigned short>(LUMP_LEAFBRUSHES);
    models       = LoadLumpArray<dmodel_t>(LUMP_MODELS);

    // Läd VIS
    printf("\tLaedt PVS...\n");
    vis = (dvis_t*) new char[header.lumps[LUMP_VISIBILITY].filelen];
    fseek(file, header.lumps[LUMP_VISIBILITY].fileofs, SEEK_SET);
    fread(vis, header.lumps[LUMP_VISIBILITY].filelen, 1, file);

    // Dekomprimiert Cluster (PVS)
    CD::CreateClusters(vis);

    // (3) Lädt Lightmaps
    printf("\tErstellt Lightmaps...\n");
    LoadLightmaps();

    // (4) Lädt Texturen
    if (GetConfigurationInt(DrawTextures)) {
        printf("\tLaedt Texturen...\n");
        LoadTextures();
    }
    // Lädt Skybox
    if(GetConfigurationInt(DrawSkybox))
        skybox.load((GetConfigurationString(DataPath) + "sky.tga").c_str());

    // (5) Koorinatensystem ändern
    printf("\tAendert Koordinatensystem...\n");
    AdaptCoordinateSystem();
    // (6) Erstellt AABBs
    CreateAABBs();

    // (6) Datei schließen
    fclose(file);

    // (4) zeigt Statistiken
    printf("\tStatistik:\n");
    printf("\t\tPolygone : %i\n", faces.size());
    printf("\t\tEckpunkte: %i\n", vertices.size());
    printf("\t\tBrushes  : %i\n", brushes.size());
    printf("\t\tEbenen   : %i\n", planes.size());
    printf("\t\tTexturen : %i\n", textures.size());
    printf("\t\tKnoten   : %i\n", nodes.size());
    printf("\t\tBlaetter : %i\n", leafs.size());
    printf("\t\tAABBs    : %i\n", leafs.size());
    printf("\t\tClusters : %i\n", vis->numclusters);
    printf("\n\tInitialisiert Fenster...\n");

    // (7) beendet Devil
    ilShutDown();
}

/*
==================================================
Liest Texturen
==================================================*/
bool LoadTextures(void) {
    char name[200];
    size_t j;

    // Speicher reservieren
    textures.resize(texinfos.size(), 0);

    if (!render_lightmap_only) {
        // Texturen Laden
        for (size_t i = 0; i < texinfos.size(); ++i) {
            // Setzt Pfad
            strcpy(name, GetConfigurationString(DataPath).c_str());
            strcat(name, "textures/");
            strcat(name, texinfos[i].texture);
            strcat(name, GetConfigurationString(TextureFormat).c_str());

            // Überprüfen,ob Datei schon geladen wurde
            for (j = 0; j < i; ++j) {
                if (std::string(texinfos[j].texture) == std::string(texinfos[i].texture))
                    break;
            }

            if (j == i) {
                // Lädt Textur
                if ((textures[i] = ilutGLLoadImage(name)) == 0)
                    exit(i);

                iluGammaCorrect(GetConfigurationFloat(Gamma));
                glBindTexture(GL_TEXTURE_2D, textures[i]);
                ilutGLBuildMipmaps();
                glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, GetConfigurationInt(AnisotropicFilter));
                glBindTexture(GL_TEXTURE_2D, 0);
            } else {  // verweist auf bereits geladene Textur
                textures[i] = textures[j];
            }
        }
    }

    return true;
}

/*
==================================================
Lädt Lightmaps
==================================================*/
void LoadLightmaps(void) {
    ILuint id;
    lightmaps.resize(faces.size(), 0);

    // Lädt Lightmaps
    for (size_t i = 1; i < faces.size(); ++i) {
        // Berechnet Lightmap
        ilBindImage(id = CreateLightmap(i));

        // Lädt Textur
        lightmaps[i] = ilutGLBindTexImage();

        iluGammaCorrect(GetConfigurationFloat(Gamma));
        glBindTexture(GL_TEXTURE_2D, lightmaps[i]);
        ilutGLBuildMipmaps();
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, GetConfigurationInt(AnisotropicFilter));
        glBindTexture(GL_TEXTURE_2D, 0);

        // Löscht Devil Lightmap,da OpenGL sie hat
        ilDeleteImage(id);
    }
}

/*
==================================================
Passt Koordinatensystem an
==================================================*/
/*
Quake II

        ^ z+
        |
        |
        |
        |
        |------------> y+
       /
      /
     /
    /
   <
 x+

OpenGL

        ^ y+
        |
        |
        |
        |
        |------------> x+
       /
      /
     /
    /
   <
 z+

*/

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


void AdaptCoordinateSystem(void) {
    size_t i;

    // Transformiert Vertices
    for (i = 0; i < vertices.size(); ++i) {
        SwapAxis(vertices[i].point);
    }

    // Transformiert Texturachsen
    for (i = 0; i < texinfos.size(); ++i) {
        SwapAxis(texinfos[i].vecs[0]);
        SwapAxis(texinfos[i].vecs[1]);
    }

    // Transformiert Ebenen
    for (i = 0; i < planes.size(); ++i)
        SwapAxis(planes[i].normal);

    // Transformiert AABBs
    for (i = 0; i < leafs.size(); ++i) {
        SwapAxis(leafs[i].mins);
        SwapAxis(leafs[i].maxs);
    }

    // Transformiert AABBs der Modelle
    for (i = 0;i < models.size(); ++i) {
        SwapAxis(models[i].mins);
        SwapAxis(models[i].maxs);
    }
}
