#pragma once
#include <SDL.h>
#include "IRenderedObject.h"
#include "TileManager.h"

class GameManager : public IRenderedObject
{

private:
	const int DEFAULT_SPRITE_SIZE = 64;

	bool isRunning = false;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* surface;
	SDL_Rect dstRect;

	TileManager* tileManager;

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

