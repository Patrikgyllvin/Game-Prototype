#ifndef GAME_H
#define GAME_H

#include "InputHandler.h"

#include "RenderManager.h"
#include "EntityManager.h"
#include "SoundManager.h"

#include "Level.h"

#include "Texture.h"

#include "Matrix4x4.h"

class Game
{
public:
	Game();
	~Game();

	void load();
	void cleanUp();

	void tick( InputHandler input, long dt );
	void render();

private:
	RenderManager* renderManager;
	SoundManager soundMgr;

	Level* level;
	Player* player;

	void setMenu();
	void loadLevel();
};

#endif