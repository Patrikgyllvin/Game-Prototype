#include "Player.h"

#include <iostream>

Player::Player( unsigned int UEID )
:
EntityMoving( UEID, false, false )
{}

Player::~Player()
{}

void Player::update( long dt )
{
	this->velX = 1;
}

int Player::getColor()
{
	return 0xFFFFFFFF;
}

int Player::getTexturePos()
{
	int texPos = 1;

	return texPos;
}
