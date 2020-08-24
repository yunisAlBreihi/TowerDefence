#include <iostream>
#include <SDL_image.h>
#include <cstdlib>
#include <ctime>
#include "GameManager.h"
#include "Enemy.h"

#pragma region Construction
GameManager::GameManager(const char* title, int posX, int posY, int width, int height, Uint32 flags)
{
	dijkstra = new Dijkstra();
	name = ManagerName::GameManager;

	//Create the SDL window and sets the game to running
	CreateWindow(title, posX, posY, width, height, flags);

	managers = Managers::GetInstance();
	managers->SetRenderer(renderer);
	managers->AddManager(this);
	spriteManager = new SpriteManager();
	managers->AddManager(spriteManager);
	tileManager = new TileManager();
	managers->AddManager(tileManager);
	mapManager = new MapManager();
	managers->AddManager(mapManager);
	mapReader = new MapReader();
	effectsManager = new EffectManager();
	managers->AddManager(effectsManager);
	bulletManager = new BulletManager();
	managers->AddManager(bulletManager);
	levelManager = new LevelManager();
	managers->AddManager(levelManager);
	enemyManager = new EnemyManager(dijkstra);
	managers->AddManager(enemyManager);
	towerManager = new TowerManager();
	managers->AddManager(towerManager);
	uiManager = new UIManager();
	managers->AddManager(uiManager);
}

GameManager::~GameManager()
{
	//delete sprites
	delete window;
	delete renderer;
	delete surface;
	delete grass;
	delete water;
	delete tower01;
	delete tower02;
	delete startPosition;
	delete endPosition;
	delete congratulations;
	delete gameOver;
	delete enemySmallSprite;
	delete enemyBigSprite;
	delete towerSmallSprite;
	delete towerBigSprite;

	//Delete UI
	delete gameOverUI;
	delete congratulationsUI;

	//Delete Managers
	delete uiManager;
	delete towerManager;
	delete enemyManager;
	delete levelManager;
	delete bulletManager;
	delete effectsManager;
	delete mapReader;
	delete mapManager;
	delete tileManager;
	delete spriteManager;
	delete dijkstra;
	
	//Delete SDL
	SDL_DestroyRenderer(renderer);
	renderer = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_Quit();
}
#pragma endregion Construction

#pragma region GameLoop
void GameManager::Start()
{
	//Creates sprites for background tiles
	grass = new Sprite(renderer, SpriteName::Grass, "Sprites/grass.jpg");
	water = new Sprite(renderer, SpriteName::Water, "Sprites/water.jpg");
	tower01 = new Sprite(renderer, SpriteName::RegularTowerGround, "Sprites/RegularTowerGround.jpg");
	tower02 = new Sprite(renderer, SpriteName::FrostTowerGround, "Sprites/FrostTowerGround.jpg");
	startPosition = new Sprite(renderer, SpriteName::EnemyBase, "Sprites/EnemyBase.jpg");
	endPosition = new  Sprite(renderer, SpriteName::PlayerBase, "Sprites/PlayerBase.jpg");

	//Create Sprites for Congratulations and GameOver
	congratulations = new Sprite(renderer, SpriteName::Congratulations, "Sprites/Congratulations.jpg");
	gameOver = new  Sprite(renderer, SpriteName::GameOver, "Sprites/GameOver.jpg");

	//Add sprites to ManagerSprites
	spriteManager->AddSprite(grass);
	spriteManager->AddSprite(water);
	spriteManager->AddSprite(tower01);
	spriteManager->AddSprite(tower02);
	spriteManager->AddSprite(startPosition);
	spriteManager->AddSprite(endPosition);
	spriteManager->AddSprite(congratulations);
	spriteManager->AddSprite(gameOver);

	//Creates sprites for enemies
	enemySmallSprite = new Sprite(renderer, SpriteName::SmallEnemy, "Sprites/SmallEnemy.jpg");
	enemyBigSprite = new Sprite(renderer, SpriteName::BigEnemy, "Sprites/BigEnemy.jpg");

	//Creates sprites for towers
	towerSmallSprite = new Sprite(renderer, SpriteName::RegularTower, "Sprites/RegularTower.jpg");
	towerBigSprite = new Sprite(renderer, SpriteName::FrostTower, "Sprites/FrostTower.jpg");

	//Add enemy sprites to the sprite manager
	spriteManager->AddSprite(enemySmallSprite);
	spriteManager->AddSprite(enemyBigSprite);

	//Add tower sprites to the sprite manager
	spriteManager->AddSprite(towerSmallSprite);
	spriteManager->AddSprite(towerBigSprite);

	//Creates UI objects for Congratulations and Game Over
	gameOverUI = new ScreenImageUI(managers, spriteManager->GetSprite(SpriteName::GameOver), Vector2D::Zero(), Vector2D(1280, 720));
	congratulationsUI = new ScreenImageUI(managers, spriteManager->GetSprite(SpriteName::Congratulations), Vector2D::Zero(), Vector2D(1280, 720));

	//Add UI to the UI Manager
	uiManager->AddUIObject(gameOverUI);
	uiManager->AddUIObject(congratulationsUI);

	//Create and add the maps to the map manager
	mapManager->AddMap(mapReader->ReadMap("Maps/Map_1.txt"));
	mapManager->AddMap(mapReader->ReadMap("Maps/Map_2.txt"));
	mapManager->AddMap(mapReader->ReadMap("Maps/Map_3.txt"));

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
#pragma endregion GameLoop

#pragma region ManageHealth
void GameManager::SetGameHasEnded(bool value)
{
	gameHasEnded = value;
}

void GameManager::ReducePlayerHealth(float reduceBy)
{
	playerHealth -= reduceBy;

	if (playerHealth <= 0)
	{
		levelManager->LoadGameOverScreen();
	}
}

void GameManager::IncreasePlayerHealth(float increasyBy)
{
	playerHealth += increasyBy;
}
#pragma endregion ManageHealth

#pragma region CreateGame
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
#pragma endregion CreateGame
