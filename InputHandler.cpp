#include "InputHandler.h"

InputHandler::InputHandler()
{
	for( int i = 0; i < 323; ++i )
	{
		keys[ i ] = false;
	}
}

void InputHandler::handleInput( SDL_Event* e )
{
	switch( e->type )
	{
	case SDL_KEYDOWN:
		onKeyDown( e->key.keysym.sym );
		break;
	case SDL_KEYUP:
		onKeyUp( e->key.keysym.sym );
	}
}

void InputHandler::onKeyDown( SDL_Keycode key )
{
	if( key > 0 && key < 323 )
	{
		keys[ key ] = true;
	}
}

void InputHandler::onKeyUp( SDL_Keycode key )
{
	if( key > 0 && key < 323 )
	{
		keys[ key ] = false;
	}
}