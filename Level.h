#ifndef LEVEL_H
#define LEVEL_H

#include "RenderManager.h"

#include "Tile.h"
#include "BaseTile.h"

#include "Entity.h"
#include "EntityMoving.h"

#include "Player.h"

#include "TestEntity.h"

typedef std::vector<unsigned int> ENTITY_LIST;

class Level
{
public:
    Level( RenderManager* renderManager );
    ~Level();

    template<class T>
    void createTile( int texPosX, int texPosY, bool solid, int x, int y )
    {
		map[ y * width + x ] = new T( texPosX, texPosY, solid, x, y );
    }

    Tile& getTile( int x, int y );

    void loadLevel( Player* player );

    void load();
    void tick( long dt );
	void render();

    Player& getPlayer();

private:
    std::vector<Tile*> map;

	int getHeight( int x );
	std::vector<Tile*> getColumn( int x );

	long long int playerHiX;

    unsigned long long int width;
	int height;

    RenderManager* renderManager;
    EntityManager* entityManager;

    Player* player;

    ENTITY_LIST entities;
};

#endif // LEVEL_H
