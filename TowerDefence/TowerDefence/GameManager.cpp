#include <iostream>
#include <SDL_image.h>
#include "GameManager.h"
#include "Sprite.h"
#include "EnemySmall.h"
#include "EnemyBig.h"

GameManager::GameManager(const char* title, int posX, int posY, int width, int height, Uint32 flags)
{
	tileManager = new TileManager();
	spriteManager = new SpriteManager();
	dijkstra = new Dijkstra();

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
	mapManager = new MapManager(renderer, spriteManager);
	mapReader = new MapReader();
	enemyManager = new EnemyManager(renderer, tileManager, mapManager, dijkstra);
}

GameManager::~GameManager()
{
}

void GameManager::Start()
{
	//Creates sprites for background tiles
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

	//Creates sprites for enemies
	Sprite* enemySmallSprite = new Sprite(renderer, SpriteName::EnemySmall);
	Sprite* enemyBigSprite = new Sprite(renderer, SpriteName::EnemyBig);

	spriteManager->AddSprite(enemySmallSprite);

	//Create and add the maps to the map manager
	mapManager->AddMap(mapReader->ReadMap("Maps/Map_1.txt"));
	mapManager->AddMap(mapReader->ReadMap("Maps/Map_2.txt"));
	mapManager->AddMap(mapReader->ReadMap("Maps/Map_3.txt"));

	tileManager->CreateTilesFromMap(mapManager, 1);
	//mapManager->GetMap(1)->DebugMapData();

	//Creates enemies
	enemyManager->AddEnemy(enemySmallSprite);
	enemyManager->AddEnemy(enemyBigSprite);

	enemyManager->Start();
	//enemyManager->DebugPositions();
	//mapManager->GetMap(1)->GetEnemyNumbers();
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
	enemyManager->Update();
}

void GameManager::Render()
{
	SDL_RenderClear(renderer);
	tileManager->Render();
	enemyManager->Render();
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
