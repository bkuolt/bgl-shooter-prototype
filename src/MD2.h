#ifndef MD2_H_INCLUDED
#define MD2_H_INCLUDED

#include "IL/ILUT.h"
#include <cmath>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Sound.h"
#include "Config.h"
#include "BSP.h"
#include "IDMD2.h"
#define X 0
#define Y 1
#define Z 2
#define MIN 0
#define MAX 1

int GetElapsedTime();

/*
=======================================================
Angepasste Pfade
=======================================================*/
inline std::string GetPath(void)
{
    const char *name = GetCommandLine();
    int length = strlen(GetCommandLine());

    while(name[length -1] != '\\')
        --length;
    return std::string(name + 1,name + length);
}

inline std::string GetPath(const std::string &name)
{
    return GetPath() + name;
}

/*
=======================================================
Lädt Skin
=======================================================*/
inline GLuint LoadImage(const std::string &name)
{
    char* c = (char*) (GetConfigurationString(DataPath) + name).c_str();
    GLuint texture;
    glBindTexture (GL_TEXTURE_2D,texture = ilutGLLoadImage(c));
    ilutGLBuildMipmaps();
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT,8);
    return texture;
}

inline void glutBitmapString(void *font,const char *string)
{
    for(const char *c = string;*c;++c)
        glutBitmapCharacter(font,*c);
}

/*
================================================================================================
=                                                                                              =
=                                      MD2 Model                                               =
=                                                                                              =
================================================================================================*/
class MD2
{
    public:
        struct Keyframe
        {
            float **vertices;
            char name[16];
        };
    private:
        Keyframe *keyframes;
        unsigned int *indices;
        double **texture_coords;
        size_t keyframe_count;
        size_t vertex_count;
        size_t triangle_count;
        GLuint texture;
        anim_t *animations;
        size_t animation_count;
        //-----------------------
        double **current_vertices;
        size_t current_frame;
        size_t current_animation;
        size_t fps;
        bool started;
        bool repeat;
        bool draw_last;
    public:
        /*
        ======================================================
        Konstruktoren
        ======================================================*/
        MD2(void){} // <--Überarbeiten!
        MD2(const std::string filename)
        {
            load(filename);
            started = false;
        }

        /*
        ======================================================
        Lädt Daten
        ======================================================*/
        void load(const std::string filename)
        {
            std::ifstream file;
            md2_t header;

            // öffnet Datei
            file.open(filename.c_str(),std::ifstream::binary);

            // liest Header
            file.read(reinterpret_cast<char*>(&header),sizeof(md2_t));

            keyframe_count = header.num_frames;
            vertex_count = header.num_xyz;
            triangle_count = header.num_tris;

            /*
            ======================================================
            Reserviert Speicher
            ======================================================*/
            indices = new unsigned int[triangle_count * 3];
            keyframes = new Keyframe[keyframe_count];

            for(size_t f = 0;f < keyframe_count;++f){
                keyframes[f].vertices = new float*[vertex_count];
                    for(size_t i = 0;i < vertex_count;++i)
                        keyframes[f].vertices[i] = new float[3];
            }

            texture_coords = new double*[triangle_count * 3];
            for(size_t i = 0;i < triangle_count * 3;++i)
                texture_coords[i] = new double[2];

            /*
            ======================================================
            Lädt MD2-Frames
            ======================================================*/
            frame_t *frames = new frame_t[keyframe_count];

            for(int i = 0;i < header.num_frames;++i){
                // liest ersten Teil
                file.seekg(header.ofs_frames + (i * header.framesize),
                           std::ios_base::beg);
                file.read(reinterpret_cast<char*>(&frames[i]),40);
                frames[i].verts = new vertex_t[header.num_xyz];
                // liest zweiten Teil
                file.seekg(header.ofs_frames + (i * header.framesize) + 40,
                           std::ios_base::beg);
                file.read(reinterpret_cast<char*>(frames[i].verts),header.num_xyz * sizeof(vertex_t));
            }

            for(size_t f = 0;f < keyframe_count;++f){
                strcpy(keyframes[f].name,frames[f].name);
                for(size_t v = 0;v < vertex_count;++v)
                    for(size_t c = 0;c < 3;++c)
                        keyframes[f].vertices[v][c] = (frames[f].verts[v].v[c] * frames[f].scale[c]) +  frames[f].translate[c];
            }

            for(int i = 0;i < header.num_frames;++i)
                frames[i].verts;
            delete[] frames;

            /*
            ======================================================
            Lädt MD2-Texturkoordinaten
            ======================================================*/
            tex_coord_t *sts = new tex_coord_t[header.num_st];

            file.seekg(header.ofs_st,std::ios_base::beg);
            file.read(reinterpret_cast<char*>(sts),sizeof(tex_coord_t) * header.num_st);

            /*
            ======================================================
            Lädt MD2-Indices
            ======================================================*/
            triangle_t *triangles = new triangle_t[header.num_tris];

            file.seekg(header.ofs_tris,std::ios_base::beg);
            file.read(reinterpret_cast<char*>(triangles),sizeof(triangle_t) * header.num_tris);

            for(size_t t = 0;t < header.num_tris;++t)
                for(size_t v = 0;v < 3;++v)
                    indices[(3 * t) + v] = triangles[t].index_xyz[v];

            /*
            ======================================================
            Formatiert Texturkoordinaten
            ======================================================*/
            for(size_t t = 0;t < header.num_tris;++t)
                for(size_t v = 0;v < 3;++v){
                    int index = triangles[t].index_st[v];
                    texture_coords[(3 * t) + v][0] = ((float) sts[index].u / (float)header.skinwidth);
                    texture_coords[(3 * t) + v][1] = ((float) sts[index].v / (float)header.skinheight);
                }

            delete[] triangles;
            delete[] sts;

            /*
            ======================================================
            Lädt Textur
            ======================================================*/
            char skin[64] = "C:\igdosh.png";

            file.seekg(header.ofs_skins,std::ios_base::beg);
            file.read(skin,64);

            // DevIL
            ilInit();
            iluInit();
            ilutInit();
            ilutRenderer(ILUT_OPENGL);
            texture = LoadImage("skin.pcx");
            ilShutDown();

            /*
            ======================================================
            Erstellt Animationsliste
            ======================================================*/
            createAnimationList();

            current_vertices = new double*[vertex_count];
            for(size_t i = 0;i < vertex_count;++i)
                    current_vertices[i] = new double[3];

            /*
            =========================================================================
            Transfomiert Koordinaten (bring sie in das richtige Koordinatensystem
            =========================================================================*/
            for(size_t f = 0;f < keyframe_count;++f)
                for(size_t i = 0;i < vertex_count;++i);

            // schliest Datei
            file.close();
        }

    private:
        /*
        ======================================================
        Zeichnet aktuellen Frame
        ======================================================*/
        void render(double** const vertices) const
        {
            glPushMatrix();
            glDisable(GL_BLEND | GL_ALPHA_TEST | GL_CULL_FACE);

            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D,texture);
            glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

            glBegin(GL_TRIANGLES);
                for(size_t i = 0;i < triangle_count * 3;++i){
                    glTexCoord2dv(texture_coords[i]);
                    glVertex3dv(vertices[indices[i]]);
                }
            glEnd();
            glDisable(GL_TEXTURE_2D);
            glPopMatrix();
        }

        /*
        ======================================================
        Erstellt Animationsliste
        ======================================================*/
        void createAnimationList(void)
        {
            std::vector<anim_t> anims;
            char last_name[16];

            // Initilialisierung
            anims.push_back(anim_t());
            anims.back().first_frame = 0;
            strcpy(last_name,keyframes[0].name);

            for(size_t i = 1,c;i < keyframe_count;++i)
            {
                // Vergleichen
                for(c = 0;!isdigit(keyframes[i].name[c]);++c);
                strcpy(last_name,keyframes[i].name);
                last_name[c] = 0;

                if(0 != strncmp(last_name,keyframes[i-1].name,c)){
                    anims.back().last_frame = i - 1;
                    anims.push_back(anim_t());
                    anims.back().first_frame = i;
                }
            }

            anims.back().last_frame = keyframe_count - 1;

            /* Debug Ausgabe
            printf("Animation|| Keyframes\n");
            for(size_t i = 0;i < anims.size();++i)
                printf("%9i|| %3i bis %3i\n",i,anims[i].first_frame,anims[i].last_frame);
            */

            animations = new anim_t[animation_count = anims.size()];
            std::copy(anims.begin(),anims.end(),animations);
        }

        /*
        ===============================================
        Interpoliert Frames
        ===============================================*/
        void interpolate(double ** vertices,size_t first,size_t second,float factor)
        {
            for(size_t v = 0;v < vertex_count;++v)
                for(size_t c = 0;c < 3;++c)
                    vertices[v][c] = keyframes[first].vertices[v][c] +
                                    (keyframes[second].vertices[v][c] - keyframes[first].vertices[v][c]) * factor;
        }

        /*
        ===============================================
        Rendert Frame der Animation
        ===============================================*/
        void createFrame(size_t animation,size_t frame,float factor)
        {
            int first  = animations[animation].first_frame + frame;
            int second = animations[animation].first_frame + frame + 1;

            // korrigiert Fehler
            if(first == animations[animation].last_frame)
                first = 0,second = 1;

            // erstellt neue vertices
            interpolate(current_vertices,first,second,factor);
        }

        /*
        ======================================================
        Legt den nächsten Frame fest
        ======================================================*/
        void next(void)
        {
            if(animations[current_animation].last_frame ==
               animations[current_animation].first_frame + current_frame + 1){
                current_frame = 0;

                if(!repeat)
                    started = false; //Animation zu Ende
            }
            else
                ++current_frame;
        }
    public:
    /*
        ===============================================
        Startet angegebene Animation
        ===============================================*/
        void start(size_t animation,size_t fps,bool do_repeat)
        {
            started = true;
            repeat  = do_repeat;
            this->fps = fps;
            current_frame = 0;
            current_animation = animation;
        }

        /*
        ===============================================
        --->Animiert<---
        ===============================================*/
        void animate(void)
        {
            static int time;
            static GLuint list;
            static bool init = false;
            static int count = 0;
            float factor = 0;
            bool create = false;

            // init
            if(!init){
                list = glGenLists(1);
                init = true;
            }

            if(started)
            {
                // nächster Frame
                if(GetElapsedTime() > time + (1000 / fps))
                {
                    next();
                    factor = 0.0f;
                    create = true;
                    time = GetElapsedTime();
                    //DEBUG
                    //printf("COUNT: %i\n",count);
                    count = 0;
                }
                else{ // Inbetween Factor
                    factor =  (float) (GetElapsedTime() - time) / (1000 / fps);
                    /*Debug Ausgabe
                    printf("Frame: %i (%i)\n",
                           animations[current_animation].first_frame +current_frame,
                           animations[current_animation].last_frame);*/
                    create = true;
                    ++count;
                    }

                // Erstellt Frame
                if(create){
                    createFrame(current_animation,current_frame,factor);
                    glNewList(list,GL_COMPILE);
                        render(current_vertices);
                    glEndList();
                }
                // RENDERT
                glCallList(list);
            }
        }

        /*
        =====================================================
        Normalisiert alle Animationen des Modells auf ]-1;1[
        ======================================================*/
        void normalize(void)
        {
            float center[3];
            float extrema[3][2] = {{0.0f,0.0f},{0.0f,0.0f},{0.0f,0.0f}};

            // findet Extremwerte
            for(size_t f = 0;f < keyframe_count;++f)
                for(size_t v = 0;v < vertex_count;++v)
                    for(size_t c = 0;c < 3;++c)
                        if(keyframes[f].vertices[v][c] > extrema[c][MAX])
                            extrema[c][MAX] = keyframes[f].vertices[v][c];
                        else if(keyframes[f].vertices[v][c] < extrema[c][MIN])
                            extrema[c][MIN] = keyframes[f].vertices[v][c];

            // Mittelpunkt berechnen
            for(size_t c = 0;c < 3;++c)
                center[c] = extrema[c][MIN] + ((extrema[c][MAX]) - (extrema[c][MIN])) / 2.0f;


            // Debug: Extremwerte ausgeben
            printf("max: %f,%f,%f\n"
                   "min: %f,%f,%f\n",
                   extrema[0][MAX],extrema[1][MAX],extrema[2][MAX],
                   extrema[0][MIN],extrema[1][MIN],extrema[2][MIN]);
            printf("M: %f,%f,%f\n",center[X],center[Y],center[Z]);

            // Vertices zum Ursprung verschieben
            for(size_t f = 0;f < keyframe_count;++f)
                for(size_t v = 0;v < vertex_count;++v)
                    for(size_t c = 0;c < 3;++c)
                        keyframes[f].vertices[v][c] -= center[c];

            // Extrema mitverschieben
            for(size_t c = 0;c < 3;++c){
                extrema[c][MIN] -= center[c];
                extrema[c][MAX] -= center[c];
            }

            // Vertices normalisieren
            for(size_t f = 0;f < keyframe_count;++f)
                for(size_t v = 0;v < vertex_count;++v)
                    for(size_t c = 0;c < 3;++c)
                        keyframes[f].vertices[v][c] /= extrema[c][MAX];

        }

        /*
        ======================================================
        Gibt Information über ablaufende Animation zurück
        ======================================================*/
        bool isRunning(void) const
        {
            return started;
        }

        int GetCurrentAnimation(void) const
        {
            return (isRunning()) ? current_animation : -1;
        }

        void stop(void)
        {
            started = false;
        }
};
typedef MD2 Animation;

/*
================================================================================================
=                                                                                              =
=                                    Waffensteuerung                                           =
=                                                                                              =
================================================================================================*/
extern Sound gun;
extern Sound music;

class Weapon
{
    private:
        enum {Putting,Shooting,Idle,PuttingAway};
        MD2 weapon;
        bool active;
        bool fight;
    public:
        /*
        ======================================================
        Lädt MD2-Datei
        ======================================================*/
        Weapon(void) : active(false),fight(false)
        {
        }

        Weapon(const std::string &file) : weapon(file),active(false),fight(false)
        {
        }

        void load(const std::string &file)
        {
            weapon.load(file);
        }

        /*
        ======================================================
        Spielt Animation ab
        ======================================================*/
        void animate(void)
        {
            if(active && !fight && !weapon.isRunning())
                weapon.start(Idle,10,true);
            weapon.animate();
        }

        /*
        ======================================================
        Setzt Animationen
        ======================================================*/
        void put(void)
        {
            putaway();
        }

        void putaway(void)
        {
            if(active){
                active = false;
                weapon.stop(); // Waffe wegstecken
            }
            else
            {
                 weapon.start(Idle,10,true); // Waffe rausholen
                active = true;
            }
        }

        void startShooting(void)
        {
            fight = true;
            gun.play(true);
            gun.setSpeed(2);
            gun.setVolume(1.0);
            weapon.start(Shooting,10,true);
        }

        void stopShooting(void)
        {
            fight = false;
            gun.stop();
            weapon.start(Idle,10,true);
        }

        void idle(void)
        {
            weapon.start(Idle,10,true);
        }
};
#endif
