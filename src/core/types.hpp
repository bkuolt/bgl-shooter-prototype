/*
Copyright (C) 1997-2001 Id Software, Inc.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.
*/

#ifndef TYPES_HPP_INCLUDED
#define TYPES_HPP_INCLUDED

#include <GL/freeglut.h>
#include <GL/glew.h>
#include <cstdint>

inline int GetElapsedTime(void) {
    return glutGet(GLUT_ELAPSED_TIME);
}

typedef float vec3_t[3];
typedef unsigned char byte;

/*
========================================================================
.PAK file structures
========================================================================
*/

#define IDPAKHEADER (('K' << 24) + ('C' << 16) + ('A' << 8) + 'P')

typedef struct {
    char name[56];
    int filepos, filelen;
} dpackfile_t;

typedef struct {
    int ident; // == IDPAKHEADER
    int dirofs;
    int dirlen;
} dpackheader_t;

#define MAX_FILES_IN_PACK 4096

/*
========================================================================
PCX file format structures
========================================================================
*/

typedef struct {
    char manufacturer;
    char version;
    char encoding;
    char bits_per_pixel;
    unsigned short xmin, ymin, xmax, ymax;
    unsigned short hres, vres;
    unsigned char palette[48];
    char reserved;
    char color_planes;
    unsigned short bytes_per_line;
    unsigned short palette_type;
    char filler[58];
    unsigned char data; // unbounded
} pcx_t;

/*
========================================================================
.MD2 triangle model file format
========================================================================
*/

#define IDALIASHEADER (('2' << 24) + ('P' << 16) + ('D' << 8) + 'I')
#define ALIAS_VERSION 8

#define MAX_TRIANGLES 4096
#define MAX_VERTS 2048
#define MAX_FRAMES 512
#define MAX_MD2SKINS 32
#define MAX_SKINNAME 64

typedef struct {
    short s;
    short t;
} dstvert_t;

typedef struct {
    short index_xyz[3];
    short index_st[3];
} dtriangle_t;

typedef struct {
    byte v[3]; // scaled byte to fit in frame mins/maxs
    byte lightnormalindex;
} dtrivertx_t;

#define DTRIVERTX_V0 0
#define DTRIVERTX_V1 1
#define DTRIVERTX_V2 2
#define DTRIVERTX_LNI 3
#define DTRIVERTX_SIZE 4

typedef struct {
    float scale[3];       // multiply byte verts by this
    float translate[3];   // then add this
    char name[16];        // frame name
    dtrivertx_t verts[1]; // variable sized
} daliasframe_t;

typedef struct {
    int ident;
    int version;
    int skinwidth;
    int skinheight;
    int framesize; // byte size of each frame
    int num_skins;
    int num_xyz;
    int num_st; // greater than num_xyz for seams
    int num_tris;
    int num_glcmds; // dwords in strip/fan command list
    int num_frames;
    int ofs_skins;  // each skin is a MAX_SKINNAME string
    int ofs_st;     // byte offset from start for stverts
    int ofs_tris;   // offset for dtriangles
    int ofs_frames; // offset for first frame
    int ofs_glcmds;
    int ofs_end; // end of file
} dmdl_t;

/*
========================================================================
.SP2 sprite file format
========================================================================
*/

#define IDSPRITEHEADER (('2' << 24) + ('S' << 16) + ('D' << 8) + 'I')
#define SPRITE_VERSION 2

typedef struct {
    int width, height;
    int origin_x, origin_y;
    char name[MAX_SKINNAME];
} dsprframe_t;

typedef struct {
    int ident;
    int version;
    int numframes;
    dsprframe_t frames[1];
} dsprite_t;

/*
==============================================================================
.WAL texture file format
==============================================================================
*/

#define MIPLEVELS 4
typedef struct miptex_s {
    char name[32];
    unsigned width, height;
    unsigned offsets[MIPLEVELS];
    char animname[32];
    int flags;
    int contents;
    int value;
} miptex_t;

/*
==============================================================================
.BSP file format
==============================================================================
*/

#define IDBSPHEADER (('P' << 24) + ('S' << 16) + ('B' << 8) + 'I')
#define BSPVERSION 38

#define MAX_MAP_MODELS 1024
#define MAX_MAP_BRUSHES 8192
#define MAX_MAP_ENTITIES 2048
#define MAX_MAP_ENTSTRING 0x40000
#define MAX_MAP_TEXINFO 8192

#define MAX_MAP_AREAS 256
#define MAX_MAP_AREAPORTALS 1024
#define MAX_MAP_PLANES 65536
#define MAX_MAP_NODES 65536
#define MAX_MAP_BRUSHSIDES 65536
#define MAX_MAP_LEAFS 65536
#define MAX_MAP_VERTS 65536
#define MAX_MAP_FACES 65536
#define MAX_MAP_LEAFFACES 65536
#define MAX_MAP_LEAFBRUSHES 65536
#define MAX_MAP_PORTALS 65536
#define MAX_MAP_EDGES 128000
#define MAX_MAP_SURFEDGES 256000
#define MAX_MAP_LIGHTING 0x200000
#define MAX_MAP_VISIBILITY 0x100000

#define MAX_KEY 32
#define MAX_VALUE 1024

typedef struct {
    int fileofs, filelen;
} lump_t;

#define LUMP_ENTITIES 0
#define LUMP_PLANES 1
#define LUMP_VERTEXES 2
#define LUMP_VISIBILITY 3
#define LUMP_NODES 4
#define LUMP_TEXINFO 5
#define LUMP_FACES 6
#define LUMP_LIGHTING 7
#define LUMP_LEAFS 8
#define LUMP_LEAFFACES 9
#define LUMP_LEAFBRUSHES 10
#define LUMP_EDGES 11
#define LUMP_SURFEDGES 12
#define LUMP_MODELS 13
#define LUMP_BRUSHES 14
#define LUMP_BRUSHSIDES 15
#define LUMP_POP 16
#define LUMP_AREAS 17
#define LUMP_AREAPORTALS 18
#define HEADER_LUMPS 19

typedef struct {
    int ident;
    int version;
    lump_t lumps[HEADER_LUMPS];
} dheader_t;

typedef struct {
    float mins[3], maxs[3];
    float origin[3];
    int headnode;
    int firstface, numfaces;
} dmodel_t;

typedef struct {
    float point[3];
} dvertex_t;

#define PLANE_X 0
#define PLANE_Y 1
#define PLANE_Z 2
#define PLANE_ANYX 3
#define PLANE_ANYY 4
#define PLANE_ANYZ 5

typedef struct {
    float normal[3];
    float dist;
    int type;
} dplane_t;

#define CONTENTS_SOLID 1
#define CONTENTS_WINDOW 2
#define CONTENTS_AUX 4
#define CONTENTS_LAVA 8
#define CONTENTS_SLIME 16
#define CONTENTS_WATER 32
#define CONTENTS_MIST 64
#define LAST_VISIBLE_CONTENTS 64

#define CONTENTS_AREAPORTAL 0x8000
#define CONTENTS_PLAYERCLIP 0x10000
#define CONTENTS_MONSTERCLIP 0x20000
#define CONTENTS_CURRENT_0 0x40000
#define CONTENTS_CURRENT_90 0x80000
#define CONTENTS_CURRENT_180 0x100000
#define CONTENTS_CURRENT_270 0x200000
#define CONTENTS_CURRENT_UP 0x400000
#define CONTENTS_CURRENT_DOWN 0x800000
#define CONTENTS_ORIGIN 0x1000000
#define CONTENTS_MONSTER 0x2000000
#define CONTENTS_DEADMONSTER 0x4000000
#define CONTENTS_DETAIL 0x8000000
#define CONTENTS_TRANSLUCENT 0x10000000
#define CONTENTS_LADDER 0x20000000

#define SURF_LIGHT 0x1
#define SURF_SLICK 0x2
#define SURF_SKY 0x4
#define SURF_WARP 0x8
#define SURF_TRANS33 0x10
#define SURF_TRANS66 0x20
#define SURF_FLOWING 0x40
#define SURF_NODRAW 0x80

typedef struct {
    int planenum;
    int children[2];
    short mins[3];
    short maxs[3];
    unsigned short firstface;
    unsigned short numfaces;
} dnode_t;

typedef struct texinfo_s {
    float vecs[2][4];
    int flags;
    int value;
    char texture[32];
    int nexttexinfo;
} texinfo_t;

typedef struct {
    unsigned short v[2];
} dedge_t;

#define MAXLIGHTMAPS 4
typedef struct {
    unsigned short planenum;
    short side;
    int firstedge;
    short numedges;
    short texinfo;
    byte styles[MAXLIGHTMAPS];
    int lightofs;
} dface_t;

typedef struct {
    int contents;
    short cluster;
    short area;
    short mins[3];
    short maxs[3];
    unsigned short firstleafface;
    unsigned short numleaffaces;
    unsigned short firstleafbrush;
    unsigned short numleafbrushes;
} dleaf_t;

typedef struct {
    unsigned short planenum;
    short texinfo;
} dbrushside_t;

typedef struct {
    int firstside;
    int numsides;
    int contents;
} dbrush_t;

#define ANGLE_UP -1
#define ANGLE_DOWN -2

#define DVIS_PVS 0
#define DVIS_PHS 1
typedef struct {
    int numclusters;
    int bitofs[8][2];
} dvis_t;

typedef struct {
    int portalnum;
    int otherarea;
} dareaportal_t;

typedef struct {
    int numareaportals;
    int firstareaportal;
} darea_t;

#endif // TYPES_HPP_INCLUDED
