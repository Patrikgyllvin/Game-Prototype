#ifndef VBO_H
#define VBO_H

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include <SDL2/SDL_opengl.h>

class VBO
{
private:
	GLuint id;

public:
	void create();
	void bufferData( GLsizei size, void* data, GLenum drawMode);

	void bind();
	void unbind();

	void destroy();
};

#endif