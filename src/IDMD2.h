#ifndef		__MD2_H
#define		__MD2_H

// magic number "IDP2" or 844121161
#define MD2_ID				(('2'<<24) + ('P'<<16) + ('D'<<8) + 'I')

// model version
#define	MD2_VERSION				8

// maximum number of vertices for a MD2 model
#define MAX_MD2_VERTS			2048

#include	<fstream>



typedef float vec3_t[3];



// md2 header
typedef struct {
	int		id;					// magic number. must be equal to "IPD2"
	int		version;			// md2 version. must be equal to 8

	int		skinwidth;			// width of the texture
	int		skinheight;			// height of the texture
	int		framesize;			// size of one frame in bytes

	int		num_skins;			// number of textures
	int		num_xyz;			// number of vertices
	int		num_st;				// number of texture coordinates
	int		num_tris;			// number of triangles
	int		num_glcmds;			// number of opengl commands
	int		num_frames;			// total number of frames

	int		ofs_skins;			// offset to skin names (64 bytes each)
	int		ofs_st;				// offset to s-t texture coordinates
	int		ofs_tris;			// offset to triangles
	int		ofs_frames;			// offset to frame data
	int		ofs_glcmds;			// offset to opengl commands
	int		ofs_end;			// offset to the end of file
} md2_t;


typedef struct {
	uint16_t u;
	uint16_t v;
} tex_coord_t;

typedef struct {
    uint16_t   index_xyz[3];    // indexes to triangle's vertices
    uint16_t   index_st[3];     // indexes to vertices' texture coorinates
} triangle_t;

typedef struct {
	unsigned char	v[3];				// compressed vertex' (x, y, z) coordinates
	unsigned char	lightnormalindex;	// index to a normal vector for the lighting
} vertex_t;

typedef struct {
	float		scale[3];		// scale values
	float		translate[3];	// translation vector
	char		name[16];		// frame name
	vertex_t	*verts;		// first vertex of this frame
} frame_t;



// animation
typedef struct
{
	int		first_frame;			// first frame of the animation
	int		last_frame;				// number of frames
	int		fps;					// number of frames per second

} anim_t;
#endif	// __MD2_H
