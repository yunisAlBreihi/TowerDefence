#include "TowerManager.h"
#include "TowerSmall.h"
#include "TowerBig.h"

TowerManager::TowerManager(Managers* managers) :  managers(managers)
{
	name = ManagerName::TowerManager;
	tileManager = managers->GetManager<TileManager>(ManagerName::TileManager);
	enemyManager = managers->GetManager<EnemyManager>(ManagerName::EnemyManager);
	spriteManager = managers->GetManager<SpriteManager>(ManagerName::SpriteManager);
	bulletManager = managers->GetManager<BulletManager>(ManagerName::BulletManager);
	effectsManager = managers->GetManager<EffectsManager>(ManagerName::EffectsManager);
}

TowerManager::~TowerManager()
{ 
}

void TowerManager::Start()
{
	for (const auto& towerRow : towers)
	{
		for (TowerBase* t : towerRow)
		{
			t->Start();
		}
	}
}

void TowerManager::Update(float deltaTime)
{
	for (const auto& towerRow : towers)
	{
		for (TowerBase* t : towerRow)
		{
			t->Update(deltaTime);
		}
	}
}

void TowerManager::Render()
{
	for (const auto& towerRow : towers)
	{
		for (TowerBase* t : towerRow)
		{
			t->Render();
		}
	}
}

void TowerManager::Destroy()
{
	for (const auto& towerRow : towers)
	{
		for (TowerBase* t : towerRow)
		{
			t->Destroy();
		}
	}
}

void TowerManager::AddTower(Sprite* towerSprite)
{
	sprites.push_back(towerSprite);
}

TowerBase* TowerManager::CreateTower(Sprite* towerSprite, Vector2D position, Vector2D scale)
{
	if (towerSprite->GetSpriteName() == SpriteName::TowerSmall)
	{
		TowerSmall* tower = new TowerSmall(managers, BulletType::Regular, towerSprite, position, scale);
		return tower;
	}
	else if (towerSprite->GetSpriteName() == SpriteName::TowerBig)
	{
		TowerBig* tower = new TowerBig(managers, BulletType::Freezing, towerSprite, position, scale);
		return tower;
	}
}

void TowerManager::CreateTowers()
{
	towers.push_back(std::vector<TowerBase*>());
	towers.push_back(std::vector<TowerBase*>());
	for (Tile* tile : tileManager->GetTiles(SpriteName::tower01))
	{
		towers[0].push_back(CreateTower(sprites[0], tile->GetPosition(), tile->GetScale()));
	}

	for (Tile* tile : tileManager->GetTiles(SpriteName::tower02))
	{
		towers[1].push_back(CreateTower(sprites[1], tile->GetPosition(), tile->GetScale()));
	}
}

void TowerManager::ClearTowers()
{
	towers.clear();
}