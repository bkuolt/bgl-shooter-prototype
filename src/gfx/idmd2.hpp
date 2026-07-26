#ifndef IDMD2_HPP_INCLUDED
#define IDMD2_HPP_INCLUDED

#include <cstdint>
#include <fstream>

#define MD2_ID (('2' << 24) + ('P' << 16) + ('D' << 8) + 'I')
#define MD2_VERSION 8
#define MAX_MD2_VERTS 2048

typedef struct {
    int id;         // Magic number, must be "IDP2"
    int version;    // MD2 version, must be 8
    int skinwidth;  // Width of texture
    int skinheight; // Height of texture
    int framesize;  // Size of one frame in bytes
    int num_skins;  // Number of textures
    int num_xyz;    // Number of vertices
    int num_st;     // Number of texture coordinates
    int num_tris;   // Number of triangles
    int num_glcmds; // Number of OpenGL commands
    int num_frames; // Total number of frames
    int ofs_skins;  // Offset to skin names (64 bytes each)
    int ofs_st;     // Offset to s-t texture coordinates
    int ofs_tris;   // Offset to triangles
    int ofs_frames; // Offset to frame data
    int ofs_glcmds; // Offset to OpenGL commands
    int ofs_end;    // Offset to end of file
} md2_t;

typedef struct {
    uint16_t u;
    uint16_t v;
} tex_coord_t;

typedef struct {
    uint16_t index_xyz[3];
    uint16_t index_st[3];
} triangle_t;

typedef struct {
    unsigned char v[3];
    unsigned char lightnormalindex;
} vertex_t;

typedef struct {
    float scale[3];
    float translate[3];
    char name[16];
    vertex_t* verts;
} frame_t;

typedef struct {
    int first_frame;
    int last_frame;
    int fps;
} anim_t;

#endif // IDMD2_HPP_INCLUDED
