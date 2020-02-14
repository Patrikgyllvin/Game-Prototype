#ifndef VERTEX_H
#define VERTEX_H

#include <SDL2/SDL_opengl.h>

typedef struct {
	GLfloat pos[2];
} Vertex;

typedef struct {
	GLfloat uv[2];
} TextureCoords;

typedef struct {
	GLubyte RGBA[4];
} Color;

#endif