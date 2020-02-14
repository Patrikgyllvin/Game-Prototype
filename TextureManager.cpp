#include "TextureManager.h"

TextureManager::TextureManager(void)
{}

TextureManager::~TextureManager(void)
{
	// destroy textures
	entities.destroy();
}

void TextureManager::loadTextures()
{
	// this will be an unnecessarily LOOOOOOOOONG function... Or not...
#ifndef __APPLE__
    entities.loadTexture( "Res/Tex/Entities.png" );
#else
    entities.loadTexture( "Game.app/Contents/Resources/Res/Tex/Entities.png" );
#endif
    entities.unbind();
	texMap.insert( std::make_pair( "Entities", entities ) );
}

Texture& TextureManager::getTexture( const char* texName )
{
	for( std::map< const char*, Texture >::iterator it = texMap.begin(); it != texMap.end(); ++it )
	{
	    std::string tex = (*it).first;

		if( tex.compare( texName ) == 0 )
		{
			return (*it).second;
		}
	}

	Texture null;
	null.loadTexture( "THIS IS NOT A REAL TEXTURE. IF YOU SEE THIS, YOU'RE TRYING TO GET A TEXTURE WHICH DOESN'T EXIST!" );

	return null;
}

void TextureManager::XYtoUV( float& u, float& v, float& uEnd, float& vEnd, unsigned int posX, unsigned int posY, unsigned int w, unsigned int h, unsigned int gridW, unsigned int gridH )
{
	if( ( w & ( w - 1 ) ) != 0 )
		return;

	int numGridsW = w / gridW;
	float numGridsWnorm = 1.0F / numGridsW;

	if( ( h & ( h - 1 ) ) != 0 )
		return;

	int numGridsH = h / gridH;
	float numGridsHnorm = 1.0F / numGridsH;

	u = numGridsWnorm * posX - numGridsWnorm;
	v = numGridsHnorm * posY - numGridsHnorm;

	uEnd = numGridsWnorm * posX;
	vEnd = numGridsHnorm * posY;
}

void TextureManager::nToUV( float& u, float& v, float& uEnd, float&vEnd, unsigned int n, unsigned int imgW, unsigned int imgH, unsigned int gridW, unsigned int gridH )
{
	if( ( imgW & ( imgW - 1 ) ) != 0 )
		return;

	if( ( imgH & ( imgH - 1 ) ) != 0 )
		return;

	int numGridsW = imgW / gridW, numGridsH = imgH / gridH;

	int x = 0, y = 0;
	bool done = false;

	for( y = 0; y < numGridsH && !done; y++ )
	{
		for( int x2 = 0; x2 < numGridsW; x2++ )
		{
			if( y == 0 )
				x = x2;

			if( x + ( x2 * y ) + 1 * y == n )
			{
				done = true;
				x = x2;
				break;
			}
		}
	}
	x++;

	XYtoUV( u, v, uEnd, vEnd, x, y, imgW, imgH, gridW, gridH );
}
