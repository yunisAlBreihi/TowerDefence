#pragma once
#include <SDL.h>
#include "IRenderable.h"
#include "TileManager.h"
#include "SpriteManager.h"
#include "EnemyManager.h"
#include "MapReader.h"

class GameManager : public IRenderable
{

private:

	bool isRunning = false;
	
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* surface = nullptr;
	SDL_Rect dstRect;

	TileManager* tileManager = nullptr;
	SpriteManager* spriteManager = nullptr;
	EnemyManager* enemyManager = nullptr;
	MapManager* mapManager = nullptr;
	MapReader* mapReader = nullptr;


public:

	static const int DEFAULT_SPRITE_SIZE = 48;

private:

public:

	GameManager(const char* title, int posX, int posY, int width, int height, Uint32 flags);
	~GameManager();
	
	void Start();
	void HandleEvent();
	void Update();
	void Render();
	void Destroy();

	bool IsRunning() { return isRunning; }
};

