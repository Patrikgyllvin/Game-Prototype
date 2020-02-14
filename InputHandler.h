#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL2/SDL.h>

class InputHandler
{
public:
	InputHandler();

	bool keys[ 323 ];

	void handleInput( SDL_Event* e );

private:
	void onKeyDown( SDL_Keycode key );
	void onKeyUp( SDL_Keycode key );
};

#endif