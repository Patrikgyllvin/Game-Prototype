#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>

#ifndef __APPLE__
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>

#else

#include <OpenGL/gl3.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2_image/SDL_image.h>
#endif


#include <stdio.h>

class Texture
{
private:
	GLuint texID;
	int w, h;

public:
	Texture(void);
	~Texture(void);

	void loadTexture( const char* fileName );

	void bind();
	void unbind();

	void destroy();

	int getWidth();
	int getHeight();
};

#endif