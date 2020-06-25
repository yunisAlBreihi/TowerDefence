#include <iostream>
#include <SDL_image.h>
#include "GameManager.h"
#include "Sprite.h"

GameManager::GameManager(const char* title, int posX, int posY, int width, int height, Uint32 flags)
{
	tileManager = new TileManager();

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
}

GameManager::~GameManager()
{
}

void GameManager::Start()
{
	int col = 5;
	int rows = 5;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < col; j++)
		{
			Tile* tempTile = new Tile();
			tempTile->Start(renderer, "Sprites/daker.jpg", DEFAULT_SPRITE_SIZE, DEFAULT_SPRITE_SIZE);
			tempTile->SetPosition(Vector2D(i * DEFAULT_SPRITE_SIZE,j * DEFAULT_SPRITE_SIZE));
			tileManager->AddTile(tempTile);
		}
	}
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
	tileManager->Render();
	//tileManager->DebugPositions();
	SDL_RenderPresent(renderer);
}

void GameManager::Destroy()
{	
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_Quit();
}
