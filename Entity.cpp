#include "Entity.h"

Entity::Entity( unsigned int UEID, bool invX, bool invY )
:
UEID( UEID ),
invX( invX ),
invY( invY )
{
	this->maxHealth = getMaxHealth();
}

Entity::~Entity()
{}

unsigned int Entity::getUEID()
{
	return this->UEID;
}

int Entity::getMaxHealth()
{
	return 20;
}

void Entity::tick( long dt )
{
	this->onUpdate( dt );
}

void Entity::changeTextureLoc( const char* textureLocation )
{
	this->texChanged = true;
	this->texLoc = textureLocation;
}

int Entity::getColor()
{
	return 0xFFFFFFFF;
}

int Entity::getTexturePos()
{
	int texPos = 1;

	return texPos;
}

void Entity::setPosX( double x )
{
	this->x = x;
}

void Entity::setPosY( double y )
{
	this->y = y;
}

double Entity::getPosX()
{
	return this->x;
}

double Entity::getPosY()
{
	return this->y;
}

void Entity::setRotX( double rotX )
{
	this->rotX = rotX;
}

void Entity::setRotZ( double rotZ )
{
	this->rotZ = rotZ;
}

double Entity::getRotX()
{
	return this->rotX;
}

double Entity::getRotZ()
{
	return this->rotZ;
}

bool Entity::getInvX()
{
	return this->invX;
}

bool Entity::getInvY()
{
	return this->invY;
}
