#include "Level.h"

Level::Level( RenderManager* renderManager )
:
playerHiX( -1 ),
width( 16 ),
height( 8 ),
renderManager( renderManager )
{
    entityManager = new EntityManager();
}

Level::~Level()
{
	for( int x = 0; x < width; x++ )
		for( int y = 0; y < height; y++ )
			delete map[ y * width + x ];

	delete entityManager;
}

void Level::load()
{
}

void Level::tick( long dt )
{
	if( player->getPosX() > playerHiX && player->getPosX() < width )
	{
		int lastHeight = getHeight( (int)player->getPosX() ), y;
	
		if( lastHeight == 0 )
			y = lastHeight + ( rand() % 2 );
		else if( lastHeight == this->height - 1 )
			y = lastHeight + ( ( rand() % 2 ) - 1 );
		else
			y = lastHeight + ( ( rand() % 3 ) - 1 );
	
		int x = (int)player->getPosX() + 1;

		for( int yCopy = y; yCopy >= 0; yCopy-- )
		{
			if( yCopy == y )
				createTile<BaseTile>( 1, 1, true, x, yCopy );
			else if( yCopy >= ( y / 2 ) )
				createTile<BaseTile>( 2, 1, true, x, yCopy );
			else if( yCopy < ( y / 2 ) )
				createTile<BaseTile>( 3, 1, true, x, yCopy );
		}

		playerHiX = player->getPosX();
	}
}

void Level::render()
{
	renderManager->renderEntities( entities, *entityManager );
}

Tile& Level::getTile( int x, int y )
{
    return *map[ y * width + x ];
}

int Level::getHeight( int x )
{
	for( int y = 0; y < height; y++ )
	{
		if( getTile( x, y ).getSolid() == true )
			return y;
	}
	
	return -1;
}

std::vector<Tile*> Level::getColumn( int x )
{
	return std::vector<Tile*>(NULL);
}

void Level::loadLevel( Player* player )
{
    this->player = player;
	this->player->setPosX( 0 );
	this->player->setPosY( 1 );

	this->width = 16;
	this->height = 8;

	unsigned int ueid;
	entityManager->addEntity<TestEntity>( ueid );
	entities.push_back( ueid );

    map.reserve( width * height );

	for( int x = 0; x < width; x++ )
        for( int y = 0; y < height; y++ )
            map.push_back( new BaseTile( NULL, NULL, false, x, y ) );

	createTile<BaseTile>( 1, 1, true, 0, 0 );

   // SDL_Surface* surf = IMG_Load( "Res/Tex/Lvl.png" );

    //for( int i = 0; i < surf->w; i++ )
    //{
          //printf("asd\n");
    //}

    //SDL_FreeSurface( surf );
}

Player& Level::getPlayer()
{
    return *this->player;
}
