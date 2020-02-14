#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#ifndef __APPLE__
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#else
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#include <SDL2/SDL_opengl.h>
#endif

#include "Shader.h"

#include "Vertex.h"
#include "VBO.h"

#include "Entity.h"
#include "EntityManager.h"

#include "TextureManager.h"

#include "Matrix4x4.h"

class RenderManager
{
private:
	GLuint vao;

	VBO quad;
	VBO textureCoords;
	VBO colorBuff;

	Shader standardShader;

	Color HexToRGB( unsigned long hex );

	int OGLVersion;

	bool entitiesBound;
	
	Matrix4x4 translationMatrix;
	Matrix4x4 rotationMatrix;
	Matrix4x4 scaleMatrix;

	Matrix4x4 modelMatrix;
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;

public:
	RenderManager();
	~RenderManager();

	TextureManager* texMgr;

	void load();

	void renderEntities( std::vector<unsigned int> entityList, EntityManager& entityMgr );
};

#endif
