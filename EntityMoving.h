#ifndef ENTITY_MOVING_H
#define ENTITY_MOVING_H

#include "Entity.h"

class EntityMoving : public Entity
{
public:
	EntityMoving( unsigned int UEID, bool invX, bool invY );
	virtual ~EntityMoving();

protected:
	double velX, velY;
	double velRotX, velRotZ;

	void onUpdate( long dt );
	virtual void update( long dt ) = 0;
};

#endif
