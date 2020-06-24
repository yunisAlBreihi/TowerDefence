#include "GameManager.h"
#include <iostream>
#include <SDL_image.h>

GameManager::GameManager(const char* title, int posX, int posY, int width, int height, Uint32 flags)
{

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow("Tower Defence", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	
		if (window == nullptr)
		{
			std::cout << "Window could not be created!" << std::endl;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, 0);
	
			if (renderer == nullptr)
			{
				std::cout << "Renderer could not be created!" << std::endl;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

				isRunning = true;
			}
		}
	}
	else
	{
		isRunning = false;
	}

	//TODO: Move the sprite load to a new class when created
	surface = IMG_Load("Sprites/daker.jpg");
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	dstRect.x = 0;
	dstRect.y = 0;
	dstRect.w = 64;
	dstRect.h = 64;
}

GameManager::~GameManager()
{
}

void GameManager::Start()
{
}

void GameManager::HandleEvent()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void GameManager::Update()
{
}

void GameManager::Render()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
	SDL_RenderPresent(renderer);
}

void GameManager::Destroy()
{	
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_Quit;
}
