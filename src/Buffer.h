
template<GLenum target,GLenum aggregate,typename GLtype,GLsizei N>
class Buffer
{
};

void enable(void) const
{
	switch(state)
	{
		case GL_VERTEX_ARRAY:
			glEnableClientState(GL_VERTEX_ARRAY);
			glBindBuffer(GL_ARRAY_BUFFER,id);
			glVertexPointer(N,type_traits::name,0,0);
			break;		
		case GL_TEXTURE_COORD_ARRAY:
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBuffer(GL_ARRAY_BUFFER,id);
			glTexCoordPointer(N,type_traits::name,0,0);
			break;
		case GL_INDEX_ARRAY:
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER,id);	
			break;
	}		
}

void disable(void)
{
	switch(state)
	{
		case GL_VERTEX_ARRAY:
		case GL_TEXTURE_COORD_ARRAY:
			glEnableClientState(mode);
			glBindBuffer(GL_ARRAY_BUFFER,0);
			break;		
		case GL_INDEX_ARRAY:
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER,0);	
			break;
	}		
}


























#ifndef __BUFFER__H__
#define __BUFFER__H__
#include "GL/GL.h"
#include "GLEE.h"

template<typename GLtype,GLsizei N>
class Buffer
{
	private:
		GLtype *data;
		GLuint id;
		GLsizei count;
		GLenum target;
	public:
	    Buffer(GLenum target) : data(NULL),count(0),target(target)
		{
			glGenBuffers(1,&id)
		}

		Buffer(GLenum target,GLsizei count) : data(NULL),count(count),target(target)
		{
			glGenBuffers(1,&id)
			glBindBuffer(target,id);
			glBufferData(target,count * sizeof(GLtype) * N,NULL,usage);
			glBindBuffer(target,0);
		}

		Buffer(GLenum target,const Buffer &rhs) : data(NULL),count(0),target(target)
		{
			glGenBuffers(1,&id)
			operator=(rhs);
		}

		~Buffer(void)
		{
			glDeleteBuffers(1,&id);
		}

		Buffer& operator=(const Buffer &rhs)
		{
			GLsizei size;
			GLtype *buffer;

			// Daten zwischenspeichern
			size = rhs.count * sizeof(GLtype) * N;
			buffer = new GLtype[size];

			glBindBuffer(target,rhs.id);
			ptr = glMapBuffer(target,GL_READ_ONLY);
			std::copy(ptr,ptr + rhs,buffer);
			glUnmapBuffer(target);

			// Daten in diese VBO kopieren
			glBindBuffer(target,id);
			glBufferData(target,size,buffer,usage);

			delete[] buffer;
			return *this;
		}

		GLtype* operator[](GLuint i)
		{
			return data + (i * N);
		}

		const GLtype* operator[](GLuint i) const
		{
			return data + (i * N);
		}

		void map(void)
		{
			glBindBuffer(target,id);
			data = glMapBuffer(target,GL_READ_WRITE);
		}

		void map(void) const
		{
			glBindBuffer(target,id);
			data = glMapBuffer(target,GL_READ_ONLY);
		}

		void unmap(void) const
		{
			glBindBuffer(target,id);
			glUnmapBuffer(target);
			data = NULL;
		}

		GLtype* begin(void)
		{
			return data;
		}

		const GLtype* begin(void) const
		{
			return data;
		}

		GLtype* end(void)
		{
			return data + count * N;
		}

		const GLtype* end(void) const
		{
			return data + count * N;
		}

		GLsizei getCount(void) const
		{
			return count;
		}

		GLsizei getSize(void) const
		{
			return sizeof(GLtype) * count * N;
		}

		virtual void enable(void) const = 0;
		virtual void disable(void) const = 0;

	protected:
		void bind(void) const
		{
			glBindBuffer(target,id);
		}

		void unbind(void) const
		{
			glBindBuffer(target,0);
		}
};

class VertexBuffer : public Buffer<GLfloat,3>
{
	public:
		void enable(void) const
		{
			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3,GL_FLOAT,0,0);
		}

		void disable(void) const
		{
			glDisableClientState(GL_VERTEX_ARRAY);
		}
};

inline void DrawPrimitives(const VertexBuffer &vb,const &IndexBuffer ib)
{
	vb.enable();
	ib.enable();
	glDrawElements(GL_TRIANGLES,ib.getCount(),count,GL_UNSIGNED_INT,NULL);
	vb.disable();
	ib.disable();
}
#endif
