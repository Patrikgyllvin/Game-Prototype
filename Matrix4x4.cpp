#include "Matrix4x4.h"

Matrix4x4::Matrix4x4()
{
	this->matrix = new GLdouble[ 16 ];
}

Matrix4x4::Matrix4x4( const Matrix4x4& mat )
{
	Matrix4x4();
	
	for( int i = 0; i < 16; i++ )
		matrix[ i ] = mat.matrix[ i ];
}

Matrix4x4::~Matrix4x4()
{
	delete [] matrix;
}

void Matrix4x4::LoadIdentity()
{
	matrix[ 0 ] = 1;	matrix[ 4 ] = 0;	matrix[ 8 ] = 0;	matrix[ 12 ] = 0;
	matrix[ 1 ] = 0;	matrix[ 5 ] = 1;	matrix[ 9 ] = 0;	matrix[ 13 ] = 0;
	matrix[ 2 ] = 0;	matrix[ 6 ] = 0;	matrix[ 10 ] = 1;	matrix[ 14 ] = 0;
	matrix[ 3 ] = 0;	matrix[ 7 ] = 0;	matrix[ 11 ] = 0;	matrix[ 15 ] = 1;
}

void Matrix4x4::translate( double x, double y, double z )
{
	LoadIdentity();

	matrix[ 12 ] = x;
	matrix[ 13 ] = y;
	matrix[ 14 ] = z;
}

void Matrix4x4::rotate( double angle, bool x, bool y, bool z )
{

}

void Matrix4x4::scale( double scale, bool x, bool y, bool z )
{

}

void Matrix4x4::perspective( float fovy, float aspect, float zNear, float zFar )
{
	for( int i = 0; i < 16; i++ )
		matrix[ i ] = 0.0;

	float f = 1.0f / tan( DEGTORAD( fovy / 2.0f ) );

	matrix[ 0 ] = f / aspect;
	matrix[ 5 ] = f;
	matrix[ 10 ] = ( zFar + zNear ) / zNear - zFar;
	matrix[ 11 ] = -1.0;
	matrix[ 14 ] = 2.0f * zFar * zNear / zNear - zFar;
}