#include "VBO.h"

void VBO::create()
{
	glGenBuffers( 1, &id );
}

void VBO::bufferData( GLsizei size, GLvoid* data, GLenum drawMode)
{
	glBufferData( GL_ARRAY_BUFFER, size, data, drawMode );
}

void VBO::bind()
{
	glBindBuffer( GL_ARRAY_BUFFER, id );
}

void VBO::unbind()
{
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void VBO::destroy()
{
	glDeleteBuffers( 1, &id );
}