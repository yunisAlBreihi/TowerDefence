#pragma once
#include <vector>
#include <SDL.h>
#include "Sprite.h"
#include "TowerBase.h"
#include "TileManager.h"
#include "IRenderable.h"
#include "Managers.h"

class TowerManager : public ManagerBase
{
private:
	std::vector<Sprite*> sprites;
	std::vector<std::vector<TowerBase*>> towers;
	Managers* managers = nullptr;
	TileManager* tileManager = nullptr;
	EnemyManager* enemyManager = nullptr;
	SpriteManager* spriteManager = nullptr;
	BulletManager* bulletManager = nullptr;
	EffectsManager* effectsManager = nullptr;

public:

private:
	TowerBase* CreateTower(Sprite* towerSprite, Vector2D position, Vector2D scale);

public:
	TowerManager(Managers* managers);
	~TowerManager();

	void Start();
	void Update();
	void Render();
	void Destroy();
	void AddTower(Sprite* towerSprite);
	void CreateTowers();
	void ClearTowers();
};