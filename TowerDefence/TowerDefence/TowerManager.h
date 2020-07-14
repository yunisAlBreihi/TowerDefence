#pragma once
#include <vector>
#include <SDL.h>
#include "Sprite.h"
#include "TowerBase.h"
#include "TileManager.h"
#include "IRenderable.h"

class TowerManager
{
private:
	std::vector<Sprite*> sprites;
	std::vector<std::vector<TowerBase*>> towers;
	SDL_Renderer* renderer = nullptr;
	SpriteManager* spriteManager = nullptr;
	TileManager* tileManager = nullptr;
	EnemyManager* enemyManager = nullptr;
	BulletManager* bulletManager = nullptr;

public:

private:
	TowerBase* CreateTower(Sprite* towerSprite, Vector2D position, Vector2D scale);

public:
	TowerManager(SDL_Renderer* renderer,SpriteManager* spriteManager, TileManager* tileManager, EnemyManager* enemyManager, BulletManager* bulletManager);

	void AddTower(Sprite* towerSprite);

	void Start();
	void Update();
	void Render();
	void Destroy();
};