#ifndef MATRIX_4X4_H
#define MATRIX_4X4_H

#include <SDL2/SDL_opengl.h>

#include "MathHelper.h"

class Matrix4x4
{
public:
	Matrix4x4();
	Matrix4x4( const Matrix4x4& mat );
	
	~Matrix4x4();

	void perspective( float fovy, float aspect, float zNear, float zFar );
	
	void LoadIdentity();
	
	void translate( double x, double y, double z );
	void rotate( double angle, bool x, bool y, bool z );
	void scale( double scale, bool x, bool y, bool z );

private:
	GLdouble* matrix;
};

#endif