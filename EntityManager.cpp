#include "EntityManager.h"

EntityManager::EntityManager()
:
currUEID( 0 )
{}

EntityManager::~EntityManager()
{
	for( std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it )
	{
		delete * it;
	}
}

bool EntityManager::removeEntity( unsigned int UEID )
{
	for( std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); )
	{
		if( (*it)->getUEID() == UEID )
		{
			freeUEIDs.push_front( UEID );
			delete * it;
			it = entities.erase( it );
			return true;
		}
		else
		{
			++it;
		}
	}

	return false;
}

Entity& EntityManager::getEntityWithUEID( unsigned int UEID )
{
	for( std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it )
	{
		if( (*it)->getUEID() == UEID )
		{
			return *(*it);
		}
	}
    
    Player p( -1 );
    
    return p;
}