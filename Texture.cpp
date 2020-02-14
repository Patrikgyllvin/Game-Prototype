#include "Texture.h"

Texture::Texture(void)
{}

Texture::~Texture(void)
{}

void Texture::loadTexture( const char* fileName )
{
	SDL_Surface* tex = IMG_Load( fileName );
	
	if( tex == NULL )
	{
		fprintf( stderr, "Could not load texture: %s, %s\n", fileName, IMG_GetError() );
		return;
	}

	if( ( tex->w & ( tex->w - 1 ) ) != 0 )
	{
		fprintf( stderr, "Error loading texture: Texture is not a valid power of two-image!\n" );
		SDL_FreeSurface( tex );
		return;
	}

	if( ( tex->h & ( tex->h - 1 ) ) != 0 )
	{
		fprintf( stderr, "Error loading texture: Texture is not a valid power of two-image!\n" );
		SDL_FreeSurface( tex );
		return;
	}

	GLenum texFmt;
	GLint Bpp = tex->format->BytesPerPixel;

	if( Bpp == 4 )
	{
		if( tex->format->Rmask == 0x000000ff )
			texFmt = GL_RGBA;
		else
			texFmt = GL_BGRA;
	}
	else if( Bpp == 3 )
	{
		if( tex->format->Rmask == 0x0000ff )
			texFmt = GL_RGB;
		else
			texFmt = GL_BGR;
	}
	else
	{
		fprintf( stderr, "Error loading texture: Image is not true-color!\n" );
		SDL_FreeSurface( tex );
		return;
	}
	
	w = tex->w;
	h = tex->h;

	glGenTextures( 1, &texID );
	bind();

	int OGLVer;
	SDL_GL_GetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, &OGLVer );

	float maxA;
	glGetFloatv( GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxA );
	
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, tex->w, tex->h, 0, texFmt, GL_UNSIGNED_BYTE, tex->pixels );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );

	glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxA );

	if( OGLVer == 3 )
		glGenerateMipmap( GL_TEXTURE_2D );

	SDL_FreeSurface( tex );
}

void Texture::bind()
{
	glBindTexture( GL_TEXTURE_2D, texID );
}

void Texture::unbind()
{
	glBindTexture( GL_TEXTURE_2D, 0 );
}

void Texture::destroy()
{
	glDeleteTextures( 1, &texID );
}

int Texture::getWidth()
{
	return w;
}

int Texture::getHeight()
{
	return h;
}
