#ifndef BUFFER_HPP_INCLUDED
#define BUFFER_HPP_INCLUDED

#include <GL/glew.h>
#include <algorithm>
#include <cstddef>

template <typename GLtype, GLsizei N> class Buffer {
private:
    GLtype* data;
    GLuint id;
    GLsizei count;
    GLenum target;

public:
    Buffer(GLenum target) : data(nullptr), id(0), count(0), target(target) { glGenBuffers(1, &id); }

    Buffer(GLenum target, GLsizei count, GLenum usage = GL_STATIC_DRAW)
        : data(nullptr), id(0), count(count), target(target) {
        glGenBuffers(1, &id);
        glBindBuffer(target, id);
        glBufferData(target, count * sizeof(GLtype) * N, nullptr, usage);
        glBindBuffer(target, 0);
    }

    virtual ~Buffer(void) {
        if (id != 0) {
            glDeleteBuffers(1, &id);
        }
    }

    GLtype* operator[](GLuint i) { return data + (i * N); }
    const GLtype* operator[](GLuint i) const { return data + (i * N); }

    void map(GLenum access = GL_READ_WRITE) {
        glBindBuffer(target, id);
        data = static_cast<GLtype*>(glMapBuffer(target, access));
    }

    void unmap(void) const {
        glBindBuffer(target, id);
        glUnmapBuffer(target);
    }

    GLtype* begin(void) { return data; }
    const GLtype* begin(void) const { return data; }

    GLtype* end(void) { return data + count * N; }
    const GLtype* end(void) const { return data + count * N; }

    GLsizei getCount(void) const { return count; }
    GLsizei getSize(void) const { return sizeof(GLtype) * count * N; }

    virtual void enable(void) const = 0;
    virtual void disable(void) const = 0;

protected:
    void bind(void) const { glBindBuffer(target, id); }
    void unbind(void) const { glBindBuffer(target, 0); }
};

class VertexBuffer : public Buffer<GLfloat, 3> {
public:
    VertexBuffer(GLsizei count, GLenum usage = GL_STATIC_DRAW) : Buffer<GLfloat, 3>(GL_ARRAY_BUFFER, count, usage) {}

    void enable(void) const override {
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, 0);
    }

    void disable(void) const override { glDisableClientState(GL_VERTEX_ARRAY); }
};

#endif // BUFFER_HPP_INCLUDED
