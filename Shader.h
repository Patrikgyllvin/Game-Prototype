#ifndef SHADER_H
#define SHADER_H

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class Shader
{
private:
	GLuint progID;
public:
	void loadAndCompile( const char* vsPath, const char* fsPath );

	void bind();
	void unbind();

	void destroy();

	void uniform1i( const char* name, GLint i );
};

#endif
