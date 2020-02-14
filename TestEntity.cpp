#include "TestEntity.h"
#include <iostream>
TestEntity::TestEntity( unsigned int UEID )
:
Entity( UEID, false, false )
{
	texPos = 2;
}

TestEntity::~TestEntity()
{}

void TestEntity::onUpdate( long dt )
{}

int TestEntity::getColor()
{
	return 0xFFFFFFFF;
}

int TestEntity::getTexturePos()
{
	if( texPos > 9 )
		texPos = 2;
	
	return texPos++;
}