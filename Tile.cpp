#include "Tile.h"

Tile::Tile( int texPosX, int texPosY, bool solid, int x, int y )
:
x( x ),
y( y ),
texPosX( texPosX ),
texPosY( texPosY ),
solid( solid )
{}

Tile::~Tile()
{}

bool Tile::getSolid()
{
	return this->solid;
}