#include "Game.h"

Game::Game(void)
{
	renderManager = new RenderManager();
	level = new Level( renderManager );
}

Game::~Game(void)
{
	delete renderManager;
	delete level;
	delete player;
}

void Game::load()
{
	renderManager->load();
	
	soundMgr.init();
	soundMgr.loadSound();

	level->load();

	//testing
	loadLevel();
}

void Game::tick( InputHandler input, long dt )
{
	if( input.keys[ SDLK_UP ] )
	{
		SDL_Event e;
		e.type = SDL_QUIT;
		SDL_PushEvent( &e );


		// set menu pause...
	}

	level->tick( dt );
	
	player->tick( dt );

	soundMgr.tick();
}

void Game::render()
{
	glClear( GL_COLOR_BUFFER_BIT );
	glClearColor( ( rand() % 11 ) / 10, ( rand() % 11 ) / 10, ( rand() % 11 ) / 10, 1.0 );
	level->render();

	/*
	int a = 0;

	if( r <= 180 && r > 0 ) a = abs( r + 180 );
	else if( r > 180 && r < 360 ) a = abs( r - 180 );

	if( r >= 360 )
	{
		r = 0;
	}

	std::cout << "r: " << r << '\n';
	std::cout << "a: " << a << '\n';

	r++;*/
}

void Game::setMenu()
{
	// at pause set level dead if quit... AT PAUSEMENU-CLASS! NO HEAREH! PAUSE MENU REFERENCE TO GAME;
}

void Game::loadLevel()
{
	player = new Player(999);

	level->loadLevel( player );
}
