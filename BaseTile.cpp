#include "BaseTile.h"

BaseTile::BaseTile( int texPosX, int texPosY, bool solid, int x, int y )
:
Tile( texPosX, texPosY, solid, x, y )
{}

BaseTile::~BaseTile()
{}

void BaseTile::tick( long dt )
{}