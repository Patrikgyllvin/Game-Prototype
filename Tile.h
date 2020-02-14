#ifndef TILE_H
#define TILE_H


class Tile
{
public:
    Tile( int texPosX, int texPosY, bool solid, int x, int y );
    virtual ~Tile();

    virtual void tick( long dt ) = 0;

	bool getSolid();

private:
    int x, y, texPosX, texPosY;

    bool solid;
};

#endif // TILE_H
