#include "RenderManager.h"

RenderManager::RenderManager()
:
OGLVersion( 0 ),
entitiesBound( false )
{
	texMgr = new TextureManager();
}

RenderManager::~RenderManager()
{
    if( OGLVersion == 3 )
    {
        quad.destroy();
        textureCoords.destroy();
        colorBuff.destroy();
        standardShader.destroy();

        glDeleteVertexArrays( 1, &vao );
    }

	delete texMgr;
}

void RenderManager::load()
{
    SDL_GL_GetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, &OGLVersion );

	texMgr->loadTextures();

    if( OGLVersion == 3 )
    {
        glGenVertexArrays( 1, &vao );
        glBindVertexArray( vao );

#ifndef __APPLE__
        standardShader.loadAndCompile( "Res/Shaders/std.vs", "Res/Shaders/std.fs" );
#else
        standardShader.loadAndCompile( "Game.app/Contents/Resources/Res/Shaders/std.vs", "Game.app/Contents/Resources/Res/Shaders/std.fs" );
#endif
        
        quad.create();

        static Vertex quadVerts[] = {
            {
                { -0.5, -1.0 },
            },
            {
                { -0.5, 1.0 },
            },
            {
                { 0.5, -1.0 },
            },
            {
                { 0.5, -1.0 },
            },
            {
                { 0.5, 1.0 },
            },
            {
                { -0.5, 1.0 },
            },
        };

        quad.bind();
        quad.bufferData( sizeof( quadVerts ), quadVerts, GL_STATIC_DRAW );

        textureCoords.create();

        textureCoords.bind();
        textureCoords.bufferData( 48, NULL, GL_STREAM_DRAW );

        colorBuff.create();

        colorBuff.bind();
        colorBuff.bufferData( 48, NULL, GL_STREAM_DRAW );
        colorBuff.unbind();
    }
}

void RenderManager::renderEntities( std::vector<unsigned int> entityList, EntityManager& entityMgr )
{
    float u, v, uEnd, vEnd;

	Texture tex = texMgr->getTexture( "Entities" );

    if( OGLVersion == 3 )
    {
        for( std::vector<unsigned int>::iterator it = entityList.begin(); it != entityList.end(); ++it )
        {
            unsigned long col = entityMgr.getEntityWithUEID( (*it) ).getColor();
	    
	    Color color = HexToRGB( col );
			
            int texPos = entityMgr.getEntityWithUEID( (*it) ).getTexturePos();
			
			texMgr->nToUV( u, v, uEnd, vEnd, texPos, tex.getWidth(), tex.getHeight(), 128, 256 );

			if( entityMgr.getEntityWithUEID( (*it) ).getInvX() )
			{
				float tmp = u;
				u = uEnd;
				uEnd = tmp;
			}
			if( entityMgr.getEntityWithUEID( (*it) ).getInvY() )
			{
				float tmp = vEnd;
				vEnd = v;
				v = tmp;
			}

            TextureCoords UVs[] = {
                {
                    { u, vEnd },
                },
                {
                    { u, v },
                },
                {
                    { uEnd, vEnd },
                },
                {
                    { uEnd, vEnd },
                },
                {
                    { uEnd, v },
                },
                {
                    { u, v },
                },
            };

            textureCoords.bind();
            textureCoords.bufferData( sizeof( UVs ), UVs, GL_STREAM_DRAW );
	    
            Color Cols[] = {
                {
                    { color.RGBA[ 0 ], color.RGBA[ 1 ], color.RGBA[ 2 ], color.RGBA[ 3 ] },
                },
                {
                    { color.RGBA[ 0 ], color.RGBA[ 1 ], color.RGBA[ 2 ], color.RGBA[ 3 ] },
                },
                {
                    { color.RGBA[ 0 ], color.RGBA[ 1 ], color.RGBA[ 2 ], color.RGBA[ 3 ] },
                },
                {
                    { color.RGBA[ 0 ], color.RGBA[ 1 ], color.RGBA[ 2 ], color.RGBA[ 3 ] },
                },
                {
                    { color.RGBA[ 0 ], color.RGBA[ 1 ], color.RGBA[ 2 ], color.RGBA[ 3 ] },
                },
                {
                    { color.RGBA[ 0 ], color.RGBA[ 1 ], color.RGBA[ 2 ], color.RGBA[ 3 ] },
                },
            };

            colorBuff.bind();
            colorBuff.bufferData( sizeof( Cols ), Cols, GL_STREAM_DRAW );

            standardShader.bind();

            glEnableVertexAttribArray( 0 );
            glEnableVertexAttribArray( 1 );
            glEnableVertexAttribArray( 2 );

            if( !entitiesBound )
            {
				tex.bind();

                entitiesBound = true;
            }


            quad.bind();
            glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

            textureCoords.bind();
            glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 );

            colorBuff.bind();
            glVertexAttribPointer( 2, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*)0 );

			glDrawArrays( GL_TRIANGLES, 0, 6 );

            glDisableVertexAttribArray( 0 );
            glDisableVertexAttribArray( 1 );
            glDisableVertexAttribArray( 2 );

            standardShader.unbind();

            colorBuff.unbind();
        }
    }

    else
    {
        for( std::vector<unsigned int>::iterator it = entityList.begin(); it != entityList.end(); ++it )
        {
            unsigned long col = entityMgr.getEntityWithUEID( (*it) ).getColor();
            Color color = HexToRGB( col );

            int texPos = entityMgr.getEntityWithUEID( (*it) ).getTexturePos();

			texMgr->nToUV( u, v, uEnd, vEnd, texPos, tex.getWidth(), tex.getHeight(), 128, 256 );

			glEnable( GL_TEXTURE_2D );

			tex.bind();

            glColor4ub( color.RGBA[ 0 ], color.RGBA[ 1 ], color.RGBA[ 2 ], 255 );
            glBegin( GL_QUADS );
                glTexCoord2i( u, vEnd );
                glVertex2f( -0.5, -1.0 );

                glTexCoord2i( u, v );
                glVertex2f( -0.5, 1.0 );

                glTexCoord2i( uEnd, vEnd );
                glVertex2f( 0.5, 1.0 );

                glTexCoord2i( uEnd, vEnd );
                glVertex2f( 0.5, -1.0 );
            glEnd();
        }
    }
}

Color RenderManager::HexToRGB( unsigned long hex )
{
	GLubyte r, g, b, a;

	r = hex >> 24;
	g = hex >> 16;
	b = hex >> 8;
	a = hex;

	Color col;
	col.RGBA[ 0 ] = r;
	col.RGBA[ 1 ] = g;
	col.RGBA[ 2 ] = b;
	col.RGBA[ 3 ] = a;

	return col;
}
