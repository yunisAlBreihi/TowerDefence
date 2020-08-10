#include <iostream>
#include <SDL_image.h>
#include "GameManager.h"
#include "Sprite.h"
#include "EnemySmall.h"
#include "EnemyBig.h"

GameManager::GameManager(const char* title, int posX, int posY, int width, int height, Uint32 flags)
{
	managers = new Managers();
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
	mapManager = new MapManager(renderer, managers);
	mapReader = new MapReader();
	effectsManager = new EffectsManager(renderer);
	bulletManager = new BulletManager(renderer);
	enemyManager = new EnemyManager(renderer, managers, dijkstra);
	towerManager = new TowerManager(renderer,managers);

	managers->AddManager(tileManager);
	managers->AddManager(spriteManager);
	managers->AddManager(mapManager);
	managers->AddManager(effectsManager);
	managers->AddManager(bulletManager);
	managers->AddManager(enemyManager);
	managers->AddManager(towerManager);
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

	//Creates sprites for towers
	Sprite* towerSmallSprite = new Sprite(renderer, SpriteName::TowerSmall);
	Sprite* towerBigSprite = new Sprite(renderer, SpriteName::TowerBig);

	//Add enemy sprites to the sprite manager
	spriteManager->AddSprite(enemySmallSprite);
	spriteManager->AddSprite(enemyBigSprite);

	//Add tower sprites to the sprite manager
	spriteManager->AddSprite(towerSmallSprite);
	spriteManager->AddSprite(towerBigSprite);

	//Create and add the maps to the map manager
	mapManager->AddMap(mapReader->ReadMap("Maps/Map_1.txt"));
	mapManager->AddMap(mapReader->ReadMap("Maps/Map_2.txt"));
	mapManager->AddMap(mapReader->ReadMap("Maps/Map_3.txt"));

	tileManager->CreateTilesFromMap(mapManager, 1);
	//mapManager->GetMap(1)->DebugMapData();

	//Add enemy sprites to the enemy manager
	enemyManager->AddEnemy(enemySmallSprite);
	enemyManager->AddEnemy(enemyBigSprite);

	//Add tower sprites to the tower manager
	towerManager->AddTower(towerSmallSprite);
	towerManager->AddTower(towerBigSprite);

	//Starts the managers
	enemyManager->Start();
	towerManager->Start();
	bulletManager->Start();
	effectsManager->Start();
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
	towerManager->Update();
	bulletManager->Update();
	effectsManager->Update();
}

void GameManager::Render()
{
	SDL_RenderClear(renderer);
	tileManager->Render();
	enemyManager->Render();
	towerManager->Render();
	bulletManager->Render();
	effectsManager->Render();
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
