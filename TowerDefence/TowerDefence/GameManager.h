#pragma once
#include <SDL.h>
#include "IRenderable.h"
#include "TileManager.h"
#include "SpriteManager.h"
#include "EnemyManager.h"
#include "TowerManager.h"
#include "BulletManager.h"
#include "EffectsManager.h"
#include "MapReader.h"
#include "MapManager.h"
#include "LevelManager.h"
#include "BulletBase.h"
#include "Managers.h"

class GameManager : public IRenderable, public ManagerBase
{
private:

	bool isRunning = false;
	
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* surface = nullptr;

	Managers* managers = nullptr;
	TileManager* tileManager = nullptr;
	SpriteManager* spriteManager = nullptr;
	EnemyManager* enemyManager = nullptr;
	TowerManager* towerManager = nullptr;
	BulletManager* bulletManager = nullptr;
	EffectsManager* effectsManager = nullptr;
	MapManager* mapManager = nullptr;
	LevelManager* levelManager = nullptr;
	MapReader* mapReader = nullptr;
	Dijkstra* dijkstra = nullptr;

	//Temporary
	BulletBase* bullet = nullptr;

public:

	static const int DEFAULT_SPRITE_SIZE = 48;

private:
	void CreateWindow(const char* title, int posX, int posY, int width, int height, Uint32 flags);

public:

	GameManager(const char* title, int posX, int posY, int width, int height, Uint32 flags);
	~GameManager();
	
	void Start() override;
	void HandleEvent();
	void Update() override;
	void Render() override;
	void Destroy() override;

	bool IsRunning() { return isRunning; }
};

