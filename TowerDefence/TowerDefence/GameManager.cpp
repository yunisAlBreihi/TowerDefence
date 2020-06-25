#include <iostream>
#include <SDL_image.h>
#include "GameManager.h"
#include "Sprite.h"

GameManager::GameManager(const char* title, int posX, int posY, int width, int height, Uint32 flags)
{
	tileManager = new TileManager();
	spriteManager = new SpriteManager();

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, posX, posY, width, height, flags);

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
	mapManager = new MapManager(renderer, spriteManager, tileManager);
	mapReader = new MapReader();
}

GameManager::~GameManager()
{
}

void GameManager::Start()
{
	Sprite* grassSprite = new Sprite(renderer, SpriteName::grass);
	Sprite* waterSprite = new Sprite(renderer, SpriteName::water);
	Sprite* tower01Sprite = new Sprite(renderer, SpriteName::tower01);
	Sprite* tower02Sprite = new Sprite(renderer, SpriteName::tower02);
	Sprite* startPositionSprite = new Sprite(renderer, SpriteName::startPosition);
	Sprite* endPositionSprite = new Sprite(renderer, SpriteName::endPosition);

	spriteManager->AddSprite(grassSprite);
	spriteManager->AddSprite(waterSprite);
	spriteManager->AddSprite(tower01Sprite);
	spriteManager->AddSprite(tower02Sprite);
	spriteManager->AddSprite(startPositionSprite);
	spriteManager->AddSprite(endPositionSprite);

	mapManager->AddMap(mapReader->ReadMap("Maps/Map_1.txt"));
	mapManager->AddMap(mapReader->ReadMap("Maps/Map_2.txt"));
	mapManager->AddMap(mapReader->ReadMap("Maps/Map_3.txt"));

	mapManager->CreateMap(1);

	//int col = 5;
	//int rows = 5;
	//for (int i = 0; i < rows; i++)
	//{
	//	for (int j = 0; j < col; j++)
	//	{
	//		Tile* tempTile = new Tile(renderer, spriteManager->GetSprite(SpriteName::daker), Vector2D(0, 0), Vector2D(DEFAULT_SPRITE_SIZE, DEFAULT_SPRITE_SIZE));
	//		tempTile->SetPosition(Vector2D(i * DEFAULT_SPRITE_SIZE, j * DEFAULT_SPRITE_SIZE));
	//		tileManager->AddTile(tempTile);
	//	}
	//}
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
