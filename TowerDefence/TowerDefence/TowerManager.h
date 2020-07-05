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
	TileManager* tileManager = nullptr;

public:

private:
	TowerBase* CreateTower(Sprite* towerSprite);

public:
	TowerManager(SDL_Renderer* renderer, TileManager* tileManager);

	void AddTower(Sprite* towerSprite);

	void Start();
	void Update();
	void Render();
	void Destroy();
};