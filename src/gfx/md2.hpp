#ifndef MD2_HPP_INCLUDED
#define MD2_HPP_INCLUDED

#include "config.hpp"
#include "idmd2.hpp"
#include "ilut_compat.hpp"
#include "sound.hpp"
#include "types.hpp"
#include <GL/freeglut.h>
#include <GL/glew.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <glm/glm.hpp>
#include <memory>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>

inline std::string GetPath(void) {
    return "./";
}

inline std::string GetPath(const std::string& name) {
    return GetPath() + name;
}

inline GLuint LoadImage(const std::string& name) {
    std::string path = GetConfigurationString(DataPath) + name;
    GLuint texture = ilutGLLoadImage(const_cast<char*>(path.c_str()));
    if (texture != 0) {
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8);
    }
    return texture;
}

inline void glutBitmapString(void* font, const char* string) {
    for (const char* c = string; *c; ++c) {
        glutBitmapCharacter(font, *c);
    }
}

class MD2 {
public:
    struct Keyframe {
        std::vector<glm::vec3> vertices;
        char name[16]{};
    };

private:
    std::vector<Keyframe> keyframes;
    std::vector<unsigned int> indices;
    std::vector<glm::vec2> texture_coords;
    size_t keyframe_count{0};
    size_t vertex_count{0};
    size_t triangle_count{0};
    GLuint texture{0};
    std::vector<anim_t> animations;
    size_t animation_count{0};

    std::vector<glm::vec3> current_vertices;
    size_t current_frame{0};
    size_t current_animation{0};
    size_t fps{0};
    bool started{false};
    bool repeat{false};
    bool draw_last{false};

    GLuint display_list{0};

public:
    MD2(void) = default;

    explicit MD2(const std::string& filename) { load(filename); }

    ~MD2(void) { clean(); }

    MD2(const MD2&) = delete;
    MD2& operator=(const MD2&) = delete;

    MD2(MD2&& other) noexcept
        : keyframes(std::move(other.keyframes)),
          indices(std::move(other.indices)),
          texture_coords(std::move(other.texture_coords)),
          keyframe_count(other.keyframe_count),
          vertex_count(other.vertex_count),
          triangle_count(other.triangle_count),
          texture(other.texture),
          animations(std::move(other.animations)),
          animation_count(other.animation_count),
          current_vertices(std::move(other.current_vertices)),
          current_frame(other.current_frame),
          current_animation(other.current_animation),
          fps(other.fps),
          started(other.started),
          repeat(other.repeat),
          draw_last(other.draw_last),
          display_list(other.display_list) {
        other.texture = 0;
        other.display_list = 0;
        other.keyframe_count = 0;
    }

    MD2& operator=(MD2&& other) noexcept {
        if (this != &other) {
            clean();
            keyframes = std::move(other.keyframes);
            indices = std::move(other.indices);
            texture_coords = std::move(other.texture_coords);
            keyframe_count = other.keyframe_count;
            vertex_count = other.vertex_count;
            triangle_count = other.triangle_count;
            texture = other.texture;
            animations = std::move(other.animations);
            animation_count = other.animation_count;
            current_vertices = std::move(other.current_vertices);
            current_frame = other.current_frame;
            current_animation = other.current_animation;
            fps = other.fps;
            started = other.started;
            repeat = other.repeat;
            draw_last = other.draw_last;
            display_list = other.display_list;

            other.texture = 0;
            other.display_list = 0;
            other.keyframe_count = 0;
        }
        return *this;
    }

    void clean(void) {
        if (texture != 0) {
            glDeleteTextures(1, &texture);
            texture = 0;
        }
        if (display_list != 0) {
            glDeleteLists(display_list, 1);
            display_list = 0;
        }
    }

    void load(const std::string& filename) {
        clean();

        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open())
            return;

        md2_t header;
        file.read(reinterpret_cast<char*>(&header), sizeof(md2_t));

        keyframe_count = header.num_frames;
        vertex_count = header.num_xyz;
        triangle_count = header.num_tris;

        indices.resize(triangle_count * 3);
        keyframes.resize(keyframe_count);

        for (size_t f = 0; f < keyframe_count; ++f) {
            keyframes[f].vertices.resize(vertex_count);
        }

        texture_coords.resize(triangle_count * 3);

        std::vector<frame_t> frames(keyframe_count);
        std::vector<vertex_t> verts_buf(vertex_count);

        for (int i = 0; i < header.num_frames; ++i) {
            file.seekg(header.ofs_frames + (i * header.framesize), std::ios_base::beg);
            file.read(reinterpret_cast<char*>(&frames[i]), 40);
            file.seekg(header.ofs_frames + (i * header.framesize) + 40, std::ios_base::beg);
            file.read(reinterpret_cast<char*>(verts_buf.data()), vertex_count * sizeof(vertex_t));

            std::strncpy(keyframes[i].name, frames[i].name, 16);
            for (size_t v = 0; v < vertex_count; ++v) {
                for (size_t c = 0; c < 3; ++c) {
                    keyframes[i].vertices[v][c] =
                        (verts_buf[v].v[c] * frames[i].scale[c]) + frames[i].translate[c];
                }
            }
        }

        std::vector<tex_coord_t> sts(header.num_st);
        file.seekg(header.ofs_st, std::ios_base::beg);
        file.read(reinterpret_cast<char*>(sts.data()), sizeof(tex_coord_t) * header.num_st);

        std::vector<triangle_t> triangles(header.num_tris);
        file.seekg(header.ofs_tris, std::ios_base::beg);
        file.read(reinterpret_cast<char*>(triangles.data()), sizeof(triangle_t) * header.num_tris);

        for (size_t t = 0; t < header.num_tris; ++t) {
            for (size_t v = 0; v < 3; ++v) {
                indices[(3 * t) + v] = triangles[t].index_xyz[v];
                int index = triangles[t].index_st[v];
                texture_coords[(3 * t) + v].x =
                    (static_cast<float>(sts[index].u) / static_cast<float>(header.skinwidth));
                texture_coords[(3 * t) + v].y =
                    (static_cast<float>(sts[index].v) / static_cast<float>(header.skinheight));
            }
        }

        ilInit();
        iluInit();
        ilutInit();
        ilutRenderer(ILUT_OPENGL);
        texture = LoadImage("skin.pcx");

        createAnimationList();
        current_vertices.resize(vertex_count);
    }

private:
    void render(const std::vector<glm::vec3>& vertices) const {
        glPushMatrix();
        glDisable(GL_BLEND | GL_ALPHA_TEST | GL_CULL_FACE);

        glActiveTexture(GL_TEXTURE1);
        glDisable(GL_TEXTURE_2D);

        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

        glBegin(GL_TRIANGLES);
        for (size_t i = 0; i < indices.size(); ++i) {
            glTexCoord2f(texture_coords[i].x, texture_coords[i].y);
            glVertex3f(vertices[indices[i]].x, vertices[indices[i]].y, vertices[indices[i]].z);
        }
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    }

    void createAnimationList(void) {
        std::vector<anim_t> anims;
        char last_name[16];

        anims.push_back(anim_t());
        anims.back().first_frame = 0;
        std::strncpy(last_name, keyframes[0].name, 16);

        for (size_t i = 1, c; i < keyframe_count; ++i) {
            for (c = 0; !std::isdigit(keyframes[i].name[c]) && c < 16; ++c)
                ;
            std::strncpy(last_name, keyframes[i].name, 16);
            last_name[c] = 0;

            if (0 != std::strncmp(last_name, keyframes[i - 1].name, c)) {
                anims.back().last_frame = i - 1;
                anims.push_back(anim_t());
                anims.back().first_frame = i;
            }
        }

        anims.back().last_frame = keyframe_count - 1;
        animations = anims;
        animation_count = animations.size();
    }

    void interpolate(std::vector<glm::vec3>& vertices, size_t first, size_t second, float factor) {
        for (size_t v = 0; v < vertex_count; ++v) {
            vertices[v] = keyframes[first].vertices[v] +
                          (keyframes[second].vertices[v] - keyframes[first].vertices[v]) * factor;
        }
    }

    void createFrame(size_t animation, size_t frame, float factor) {
        int first = animations[animation].first_frame + frame;
        int second = animations[animation].first_frame + frame + 1;

        if (first == static_cast<int>(animations[animation].last_frame)) {
            first = 0;
            second = 1;
        }
        interpolate(current_vertices, first, second, factor);
    }

    void next(void) {
        if (animations[current_animation].last_frame == animations[current_animation].first_frame + current_frame + 1) {
            current_frame = 0;
            if (!repeat)
                started = false;
        } else {
            ++current_frame;
        }
    }

public:
    void start(size_t animation, size_t fps_val, bool do_repeat) {
        started = true;
        repeat = do_repeat;
        this->fps = fps_val;
        current_frame = 0;
        current_animation = animation;
    }

    void animate(void) {
        static int time_val = 0;
        float factor = 0;
        bool create = false;

        if (display_list == 0) {
            display_list = glGenLists(1);
        }

        if (started && fps > 0) {
            if (GetElapsedTime() > time_val + (1000 / static_cast<int>(fps))) {
                next();
                factor = 0.0f;
                create = true;
                time_val = GetElapsedTime();
            } else {
                factor = static_cast<float>(GetElapsedTime() - time_val) / (1000.0f / static_cast<float>(fps));
                create = true;
            }

            if (create) {
                createFrame(current_animation, current_frame, factor);
                glNewList(display_list, GL_COMPILE);
                render(current_vertices);
                glEndList();
            }
            glCallList(display_list);
        }
    }

    bool isRunning(void) const { return started; }
    int GetCurrentAnimation(void) const { return (isRunning()) ? current_animation : -1; }
    void stop(void) { started = false; }
};

typedef MD2 Animation;

extern Sound gun;
extern Sound music;

class weapon_t {
private:
    enum { Putting, Shooting, Idle, PuttingAway };
    MD2 weapon;
    bool active{false};
    bool fight{false};

public:
    weapon_t(void) = default;
    explicit weapon_t(const std::string& file) : weapon(file), active(false), fight(false) {}

    void load(const std::string& file) { weapon.load(file); }

    void animate(void) {
        if (active && !fight && !weapon.isRunning()) {
            weapon.start(Idle, 10, true);
        }
        weapon.animate();
    }

    void put(void) { putaway(); }

    void putaway(void) {
        if (active) {
            active = false;
            weapon.stop();
        } else {
            weapon.start(Idle, 10, true);
            active = true;
        }
    }

    void startShooting(void) {
        fight = true;
        gun.play(true);
        gun.setSpeed(2);
        gun.setVolume(1.0);
        weapon.start(Shooting, 10, true);
    }

    void stopShooting(void) {
        fight = false;
        gun.stop();
        weapon.start(Idle, 10, true);
    }

    void idle(void) { weapon.start(Idle, 10, true); }
};

#endif // MD2_HPP_INCLUDED
