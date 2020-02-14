#include "Shader.h"


void Shader::loadAndCompile( const char* vsFilePath, const char* fsFilePath )
{
	// vs and fs IDs
	GLuint vsID = glCreateShader( GL_VERTEX_SHADER );
	GLuint fsID = glCreateShader( GL_FRAGMENT_SHADER );

	// load vs shader
	std::string vsCode = "";
	std::ifstream vsStream( vsFilePath, std::ios::in );

	fprintf( stdout, "loading shader: %s\n", vsFilePath );

	if( vsStream.is_open() )
	{
		std::string line = "";
		while( std::getline( vsStream, line ) )
			vsCode += line + '\n';
		vsStream.close();
	}
	else
	{
		fprintf( stdout, "Could not find shader: %s\n", vsFilePath );
	}

	// load fs shader
	std::string fsCode;
	std::ifstream fsStream( fsFilePath, std::ios::in );

	fprintf( stdout, "loading shader: %s\n", fsFilePath );

	if( fsStream.is_open() )
	{
		std::string line = "";
		while( std::getline( fsStream, line ) )
			fsCode += line + '\n';
		fsStream.close();
	}
	else
	{
		fprintf( stdout, "Could not find shader: %s\n", fsFilePath );
	}

	// compile...
	GLint result = GL_FALSE;
	int infoLogLength;

	// vs
	fprintf( stdout, "Compiling shader: %s\n", vsFilePath );
	
	const char* vsSource = vsCode.c_str();
	glShaderSource( vsID, 1, &vsSource, NULL );
	glCompileShader( vsID );

	glGetShaderiv( vsID, GL_COMPILE_STATUS, &result );
	glGetShaderiv( vsID, GL_INFO_LOG_LENGTH, &infoLogLength );
	if( infoLogLength > 0 )
	{
		std::vector<char> vsErrorMsg( infoLogLength );
		glGetShaderInfoLog( vsID, infoLogLength, NULL, &vsErrorMsg[ 0 ] );
		fprintf( stdout, "%s\n", &vsErrorMsg[ 0 ] );
	}

	// fs
	fprintf( stdout, "Compiling shader: %s\n", fsFilePath );
	
	const char* fsSource = fsCode.c_str();
	glShaderSource( fsID, 1, &fsSource, NULL );
	glCompileShader( fsID );

	glGetShaderiv( fsID, GL_COMPILE_STATUS, &result );
	glGetShaderiv( fsID, GL_INFO_LOG_LENGTH, &infoLogLength );
	if( infoLogLength > 0 )
	{
		std::vector<char> fsErrorMsg( infoLogLength );
		glGetShaderInfoLog( fsID, infoLogLength, NULL, &fsErrorMsg[ 0 ] );
		fprintf( stdout, "%s\n", &fsErrorMsg[ 0 ] );
	}

	fprintf( stdout, "Linking program...\n" );
	GLuint tmpProgID = glCreateProgram();
	glAttachShader( tmpProgID, vsID );
	glAttachShader( tmpProgID, fsID );
	glLinkProgram( tmpProgID );

	glGetProgramiv( tmpProgID, GL_LINK_STATUS, &result );
	glGetProgramiv( tmpProgID, GL_INFO_LOG_LENGTH, &infoLogLength );
	if( infoLogLength > 0 )
	{
		std::vector<char> progErrorMsg( infoLogLength );
		glGetProgramInfoLog( tmpProgID, infoLogLength, NULL, &progErrorMsg[ 0 ] );
		fprintf( stdout, "%s\n", &progErrorMsg[ 0 ] );
	}

	glDeleteShader( vsID );
	glDeleteShader( fsID );

	this->progID = tmpProgID;
}

void Shader::bind()
{
	glUseProgram( progID );
}

void Shader::unbind()
{
	glUseProgram( NULL );
}

void Shader::destroy()
{
	glDeleteProgram( progID );
}

void Shader::uniform1i( const char* name, GLint i )
{
	glUniform1i( glGetUniformLocation( this->progID, name ), i );
}