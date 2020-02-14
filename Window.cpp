#include "Window.h"

Window::Window()
:
maxFPS( 60 ),
windowed( false ),
running( false ),
OGLVersion( 0 )
{
	this->game = new Game();
	this->inputHandler = new InputHandler();
}

Window::~Window()
{}

int Window::setUpWindow()
{
	for( int i = 0; i < SDL_GetNumVideoDisplays(); ++i )
	{
		int err = SDL_GetCurrentDisplayMode( i, &mode );

		if( err != 0 )
		{
			fprintf( stderr, "Could not get display mode for display #%d: %s \n", i, SDL_GetError() );
			return -1;
		}
		else
		{
			fprintf( stdout, "Display #%d: Current display mode is %dx%dpx @ %dhz. \n", i, mode.w, mode.h, mode.refresh_rate );
		}
	}

	this->setMaxFPS( mode.refresh_rate );

	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );

	
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
	if( SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ) != 0 )
	{
		fprintf( stderr, "Double-buffering not supported on your system, tearing may occur!\n" );
	}

	if( SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1 ) != 0 )
	{
		fprintf( stderr, "Multisampling not available!\n" );
	}

	if( SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, 4 ) != 0 )
	{
		fprintf( stderr, "Multisampling not available!\n" );
	}
		if( ( window = SDL_CreateWindow( "Blabarspaj", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_OPENGL ) ) == NULL )
	{
		fprintf( stderr, "Could not create window: %s \n", SDL_GetError() );
		return -1;
	}

	SDL_GetWindowSize( window, &winW, &winH );


		OGLVersion = 3;
		
	glContext = SDL_GL_CreateContext( window );

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if( err != GLEW_OK )
	{
		fprintf( stderr, "Could not initialize GLEW! %s\n", glewGetErrorString( err ) );
		return -1;
	}

	return 0;
}

void Window::setMaxFPS( int fps )
{
	if( fps > 0 )
		this->maxFPS = fps;
}

int Window::setUpGL()
{
    if( OGLVersion == 3 )
    {
        glViewport( 0, 0, winW, winH );
    }
    else
    {
        glViewport( 0, 0, winW, winH );

        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glFrustum( -1, 1, -1, 1, -1, 1 );
        glMatrixMode( GL_MODELVIEW );
    }

	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	return 0;
}

void Window::cleanUp()
{
	delete inputHandler;
	delete game;

	SDL_GL_DeleteContext( glContext );
	SDL_DestroyWindow( window );

	IMG_Quit();
	SDL_Quit();
}

void Window::processEvent( SDL_Event* e )
{
	switch( e->type )
	{
	case SDL_KEYDOWN:
		inputHandler->handleInput( e );
		break;
	case SDL_KEYUP:
		inputHandler->handleInput( e );
		break;
	case SDL_QUIT:
		this->running = false;
		break;
	case SDL_WINDOWEVENT:
		switch( e->window.event )
		{
		case SDL_WINDOWEVENT_RESIZED:
			this->winW = e->window.data1;
			this->winH = e->window.data2;

			glViewport( 0, 0, winW, winH );
		}
	}
}

void Window::getInput(void*data)
{
    
}

void Window::run()
{
	game->load();

	SDL_Event e;

	long lastTime = SDL_GetTicks();
	long currTime = 0;
	long deltaTime = 0;
	long lapseTime = 0;
	int frames = 0;

	long millisPerTick = 1000 / maxFPS;

	running = true;

	while( running )
	{
		millisPerTick = 1000 / maxFPS;
		currTime = SDL_GetTicks();
		deltaTime += currTime - lastTime;
		lastTime = currTime;

		lapseTime += deltaTime;

		if( deltaTime < millisPerTick )
		{
			tick( deltaTime );

			SDL_Delay( millisPerTick - deltaTime );
		}
		else
		{
			// render
			doRender();

			frames++;

			deltaTime = 0;

			if( lapseTime > 1000 )
			{
				printf( "fps: %d\n", frames );

				frames = 0;
				lapseTime = 0;
			}
		}

		while( SDL_PollEvent( &e ) )
			processEvent( &e );
	}
}

void Window::tick( long dt )
{
	game->tick( *inputHandler, dt );
}

void Window::doRender()
{
	game->render();

	SDL_GL_SwapWindow( window );
}

int main( int argc, char** argv )
{
	Window game;

	srand( time( NULL ) );

	SDL_Init( SDL_INIT_EVERYTHING );

	if( game.setUpWindow() != 0 )
	{
		fprintf( stderr, "Error: Could not create Window!\n" );

		return -1;
	}

	if( game.setUpGL() != 0 )
	{
		fprintf( stderr, "Error: could not initialize OpenGL correctly!\n" );

		return -1;
	}

	game.run();

	game.cleanUp();

	return 0;
}
