#include "EntityMoving.h"

EntityMoving::EntityMoving( unsigned int UEID, bool invX, bool invY )
:
Entity( UEID, invX, invY )
{}

EntityMoving::~EntityMoving()
{}

void EntityMoving::onUpdate( long dt )
{
    this->x += velX * dt;
    this->y += velY * dt;

	this->rotX += velRotX * dt;
	this->rotZ += velRotZ * dt;

	this->update( dt );
}
