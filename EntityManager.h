#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"
#include "Player.h"

#include <deque>
#include <vector>

#include <iostream>

class EntityManager
{
private:
	std::deque<unsigned int> freeUEIDs;
	unsigned int currUEID;
	std::vector<Entity*> entities;

public:
	EntityManager();
	~EntityManager();

	template<class T>
	void addEntity( unsigned int& UEID )
	{
		if( freeUEIDs.empty() )
		{
			Entity* e = new T( ++currUEID );
			UEID = e->getUEID();
			entities.push_back( e );
		}
		else
		{
			Entity* e = new T( freeUEIDs.front() );
			UEID = e->getUEID();
			freeUEIDs.pop_front();
			entities.push_back( e );
		}
	}

	bool removeEntity( unsigned int UEID );

	Entity& getEntityWithUEID( unsigned int UEID );
};

#endif
