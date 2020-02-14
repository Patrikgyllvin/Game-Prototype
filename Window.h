#ifndef WINDOW_H
#define WINDOW_H

#include "Game.h"
#include "InputHandler.h"

#include <stdlib.h>
#include <stdio.h>

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include <SDL2/SDL.h>

#ifdef _DEBUG
  #include <vld.h>
#endif

class Window {
public:
	~Window();
	Window();

	void setMaxFPS( int fps );

	int setUpWindow();
	int setUpGL();

	void run();
	void cleanUp();
    
    void getInput( void* data );
    
private:
	Game* game;

	InputHandler* inputHandler;

	SDL_Window *window;
	SDL_DisplayMode mode;

	int winW, winH;

    int OGLVersion;

	bool windowed;

	SDL_GLContext glContext;

	void processEvent( SDL_Event* e );

	void tick( long dt );
	void doRender();

	int maxFPS;
	bool running;
};

#endif
