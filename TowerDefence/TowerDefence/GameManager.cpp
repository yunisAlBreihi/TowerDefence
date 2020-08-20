#include <iostream>
#include <SDL_image.h>
#include "GameManager.h"
#include "Sprite.h"
#include "EnemySmall.h"
#include "EnemyBig.h"
#include "ScreenUI.h"


GameManager::GameManager(const char* title, int posX, int posY, int width, int height, Uint32 flags)
{
	dijkstra = new Dijkstra();
	name = ManagerName::GameManager;

	//Create the SDL window and sets the game to running
	CreateWindow(title, posX, posY, width, height, flags);

	managers = new Managers(renderer);
	managers->AddManager(this);
	spriteManager = new SpriteManager();
	managers->AddManager(spriteManager);
	tileManager = new TileManager();
	managers->AddManager(tileManager);
	mapManager = new MapManager(managers);
	managers->AddManager(mapManager);
	mapReader = new MapReader();
	effectsManager = new EffectsManager(managers);
	managers->AddManager(effectsManager);
	bulletManager = new BulletManager(managers);
	managers->AddManager(bulletManager);
	levelManager = new LevelManager(managers);
	managers->AddManager(levelManager);
	enemyManager = new EnemyManager(managers, dijkstra);
	managers->AddManager(enemyManager);
	towerManager = new TowerManager(managers);
	managers->AddManager(towerManager);
	uiManager = new UIManager(managers);
	managers->AddManager(uiManager);
}

GameManager::~GameManager()
{
}

void GameManager::Start()
{
	//Creates sprites for background tiles
	Sprite* grass = new Sprite(renderer, SpriteName::Grass);
	Sprite* water = new Sprite(renderer, SpriteName::Water);
	Sprite* tower01 = new Sprite(renderer, SpriteName::Tower01);
	Sprite* tower02 = new Sprite(renderer, SpriteName::Tower02);
	Sprite* startPosition = new Sprite(renderer, SpriteName::StartPosition);
	Sprite* endPosition = new Sprite(renderer, SpriteName::EndPosition);

	//Create Sprites for Congratulations and GameOver
	Sprite* congratulations = new Sprite(renderer, SpriteName::Congratulations);
	Sprite* gameOver = new Sprite(renderer, SpriteName::GameOver);

	spriteManager->AddSprite(grass);
	spriteManager->AddSprite(water);
	spriteManager->AddSprite(tower01);
	spriteManager->AddSprite(tower02);
	spriteManager->AddSprite(startPosition);
	spriteManager->AddSprite(endPosition);
	spriteManager->AddSprite(congratulations);
	spriteManager->AddSprite(gameOver);

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

	//Creates UI objects for Congratulations and Game Over
	ScreenUI* gameOverUI = new ScreenUI(managers, spriteManager->GetSprite(SpriteName::GameOver), Vector2D::Zero(), Vector2D(1280, 720));
	ScreenUI* congratulationsUI = new ScreenUI(managers, spriteManager->GetSprite(SpriteName::Congratulations), Vector2D::Zero(), Vector2D(1280, 720));

	//Add UI to the UI Manager
	uiManager->AddUIObject(gameOverUI);
	uiManager->AddUIObject(congratulationsUI);

	//Create and add the maps to the map manager
	mapManager->AddMap(mapReader->ReadMap("Maps/Map_1.txt"));
	mapManager->AddMap(mapReader->ReadMap("Maps/Map_2.txt"));
	mapManager->AddMap(mapReader->ReadMap("Maps/Map_3.txt"));

	//Add enemy sprites to the enemy manager
	enemyManager->AddEnemyType(enemySmallSprite);
	enemyManager->AddEnemyType(enemyBigSprite);

	//Starts the managers
	levelManager->Start();
	enemyManager->Start();
	towerManager->Start();
	bulletManager->Start();
	effectsManager->Start();
	uiManager->Start();
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

void GameManager::Update(float deltaTime)
{
	if (gameHasEnded == false)
	{
		enemyManager->Update(deltaTime);
		towerManager->Update(deltaTime);
		bulletManager->Update(deltaTime);
		effectsManager->Update(deltaTime);
	}
	uiManager->Update(deltaTime);
	levelManager->Update(deltaTime);
}

void GameManager::Render()
{
	SDL_RenderClear(renderer);
	if (gameHasEnded == false)
	{
		tileManager->Render();
		enemyManager->Render();
		towerManager->Render();
		bulletManager->Render();
		effectsManager->Render();
	}
	uiManager->Render();
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

void GameManager::SetGameHasEnded(bool value)
{
	gameHasEnded = value;
}

void GameManager::ReducePlayerHealth(unsigned int reduceBy)
{
	playerHealth -= reduceBy;

	if (playerHealth <= 0)
	{
		levelManager->LoadGameOverScreen();
	}
}

void GameManager::IncreasePlayerHealth(unsigned int increasyBy)
{
	playerHealth += increasyBy;
}

void GameManager::CreateWindow(const char* title, int posX, int posY, int width, int height, Uint32 flags)
{
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
}
