#pragma once
#include <SDL.h>
#include "IRenderable.h"
#include "TileManager.h"
#include "SpriteManager.h"
#include "EnemyManager.h"
#include "TowerManager.h"
#include "BulletManager.h"
#include "EffectManager.h"
#include "MapReader.h"
#include "MapManager.h"
#include "LevelManager.h"
#include "UIManager.h"
#include "BulletBase.h"
#include "Managers.h"
#include "UIBase.h"
#include "Sprite.h"
#include "ScreenImageUI.h"

class GameManager : public IRenderable, public ManagerBase
{
private:
	Managers* managers = nullptr;
	TileManager* tileManager = nullptr;
	SpriteManager* spriteManager = nullptr;
	EnemyManager* enemyManager = nullptr;
	TowerManager* towerManager = nullptr;
	BulletManager* bulletManager = nullptr;
	EffectManager* effectsManager = nullptr;
	MapManager* mapManager = nullptr;
	LevelManager* levelManager = nullptr;
	UIManager* uiManager = nullptr;
	MapReader* mapReader = nullptr;
	Dijkstra* dijkstra = nullptr;

	//SDL
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* surface = nullptr;

	//Sprites
	Sprite* grassSprite = nullptr;
	Sprite* waterSprite = nullptr;
	Sprite* regularTowerGroundSprite = nullptr;
	Sprite* frostTowerGroundSprite = nullptr;
	Sprite* enemyBaseSprite = nullptr;
	Sprite* playerBaseSprite = nullptr;
	Sprite* congratulationsSprite = nullptr;
	Sprite* gameOverSprite = nullptr;
	Sprite* smallEnemySprite = nullptr;
	Sprite* bigEnemySprite = nullptr;
	Sprite* regularTowerSprite = nullptr;
	Sprite* frostTowerSprite = nullptr;
	Sprite* regularBulletSprite = nullptr;
	Sprite* frostBulletSprite = nullptr;
	Sprite* regularExplosionSprite = nullptr;
	Sprite* frostExplosionSprite = nullptr;

	//UI
	ScreenImageUI* gameOverUI = nullptr;
	ScreenImageUI* congratulationsUI = nullptr;

	//For Game loop
	bool isRunning = false;
	bool gameHasEnded = false;

	//Player Attributes
	float playerHealth = 10.0f;

private:
	void CreateWindow(const char* title, int posX, int posY, int width, int height, Uint32 flags);

public:
	GameManager(const char* title, int posX, int posY, int width, int height, Uint32 flags);
	~GameManager();

	void Start() override;
	void HandleEvent();
	void Update(float deltaTime) override;
	void Render() override;

	bool IsRunning() { return isRunning; }
	bool GameHasEnded() { return gameHasEnded; }
	void SetGameHasEnded(bool value);

	void ReducePlayerHealth(float reduceBy);
	void IncreasePlayerHealth(float increasyBy);
};

