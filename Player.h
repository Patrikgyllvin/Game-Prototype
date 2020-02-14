#ifndef PLAYER_H
#define PLAYER_H

#include "EntityMoving.h"

class Player : public EntityMoving
{
public:
	Player( unsigned int UEID );
	~Player();

private:
	virtual void update( long dt );
	int getTexturePos();
	int getColor();
};

#endif
