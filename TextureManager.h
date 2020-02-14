#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <math.h>

#include "Texture.h"

class TextureManager
{
public:
	TextureManager(void);
	~TextureManager(void);

	void loadTextures();

	Texture& getTexture( const char* texName );

	void XYtoUV( float& u, float& v, float& uEnd, float& vEnd, unsigned int posX, unsigned int posY, unsigned int w, unsigned int h, unsigned int gridW, unsigned int gridH );
	void nToUV( float& u, float& v, float& uEnd, float&vEnd, unsigned int n, unsigned int imgW, unsigned int imgH, unsigned int gridW, unsigned int gridH );

private:
	std::map< const char*, Texture > texMap;
	
	Texture entities;
	Texture tiles;
};

#endif