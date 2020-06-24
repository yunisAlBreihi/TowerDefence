#pragma once
#include <SDL.h>

class GameManager
{

private:

	bool isRunning = false;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Rect dstRect;

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

