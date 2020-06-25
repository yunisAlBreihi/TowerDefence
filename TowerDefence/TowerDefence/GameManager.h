#pragma once
#include <SDL.h>
#include "IRenderable.h"
#include "TileManager.h"
#include "SpriteManager.h"

class GameManager : public IRenderable
{

private:
	const int DEFAULT_SPRITE_SIZE = 64;

	bool isRunning = false;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* surface;
	SDL_Rect dstRect;

	TileManager* tileManager;
	SpriteManager* spriteManager;

public:

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

