#ifndef BASETILE_H
#define BASETILE_H

#include "Tile.h"

class BaseTile : public Tile
{
public:
    BaseTile( int texPosX, int texPosY, bool solid, int x, int y );
    virtual ~BaseTile();

	void tick( long dt );

private:
};

#endif