#ifndef TESTENTITY_H
#define TESTENTITY_H

#include "Entity.h"

#include "FrameTimer.h"

class TestEntity : public Entity
{
public:
	TestEntity( unsigned int UEID );
	virtual ~TestEntity();

	int getTexturePos();
	int getColor();

private:
	int texPos;

	FrameTimer anim;

	void onUpdate( long dt );
};

#endif
