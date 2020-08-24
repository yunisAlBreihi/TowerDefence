#pragma once
#include <vector>
#include <SDL.h>
#include "Sprite.h"
#include "TowerBase.h"
#include "TileManager.h"
#include "IRenderable.h"
#include "Managers.h"

class TowerManager : public IRenderable, public ManagerBase
{
private:
	Managers* managers = nullptr;
	TileManager* tileManager = nullptr;
	EnemyManager* enemyManager = nullptr;
	SpriteManager* spriteManager = nullptr;
	BulletManager* bulletManager = nullptr;
	EffectManager* effectsManager = nullptr;

	std::vector<TowerBase*> towers;

private:
	void CreateTower(Sprite* sprite, Vector2D position, Vector2D scale);

public:
	TowerManager();

	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;

	void CreateTowers();
	void ClearTowers();

	TowerBase* GetInactiveTowerOfType(BulletType bulletType);
};