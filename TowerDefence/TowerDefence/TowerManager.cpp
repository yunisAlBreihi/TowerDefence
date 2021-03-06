#include "TowerManager.h"
#include "RegularTower.h"
#include "FrostTower.h"

#pragma region Construction
TowerManager::TowerManager()
{
	managers = Managers::GetInstance();
	name = ManagerName::TowerManager;
	tileManager = managers->GetManager<TileManager>(ManagerName::TileManager);
	enemyManager = managers->GetManager<EnemyManager>(ManagerName::EnemyManager);
	spriteManager = managers->GetManager<SpriteManager>(ManagerName::SpriteManager);
	bulletManager = managers->GetManager<BulletManager>(ManagerName::BulletManager);
	effectsManager = managers->GetManager<EffectManager>(ManagerName::EffectsManager);
}
#pragma endregion Construction

#pragma region GameLoop
void TowerManager::Start()
{
	for (const auto& tower : towers)
	{
		tower->Start();
	}
}

void TowerManager::Update(float deltaTime)
{
	for (const auto& tower : towers)
	{
		tower->Update(deltaTime);
	}
}

void TowerManager::Render()
{
	for (const auto& tower : towers)
	{
		tower->Render();
	}
}
#pragma endregion GameLoop

#pragma region ManageTowers
void TowerManager::CreateTower(Sprite* sprite, Vector2D position, Vector2D scale)
{
	if (sprite->GetSpriteName() == SpriteName::RegularTower)
	{
		RegularTower* towerSmall = (RegularTower*)GetInactiveTowerOfType(BulletType::Regular);
		if (towerSmall == nullptr)
		{
			towerSmall = new RegularTower(BulletType::Regular, sprite, position, scale);
			towers.push_back(towerSmall);
		}
		else
		{
			towerSmall->Reset(BulletType::Regular, sprite, position, scale);
		}
	}
	else if (sprite->GetSpriteName() == SpriteName::FrostTower)
	{
		FrostTower* towerBig = (FrostTower*)GetInactiveTowerOfType(BulletType::Freezing);
		if (towerBig == nullptr)
		{
			towerBig = new FrostTower(BulletType::Freezing, sprite, position, scale);
			towers.push_back(towerBig);
		}
		else
		{
			towerBig->Reset(BulletType::Freezing, sprite, position, scale);
		}
	}
}

void TowerManager::CreateTowers()
{
	Sprite* sprite = nullptr;
	for (const auto& tile : tileManager->GetTilesWithSprite(SpriteName::RegularTowerGround))
	{
		if (tile->IsActive() == true)
		{
			sprite = spriteManager->GetSprite(SpriteName::RegularTower);
			CreateTower(sprite, tile->GetPosition(), tile->GetScale());
		}
	}

	for (const auto& tile : tileManager->GetTilesWithSprite(SpriteName::FrostTowerGround))
	{
		if (tile->IsActive() == true)
		{
			sprite = spriteManager->GetSprite(SpriteName::FrostTower);
			CreateTower(sprite, tile->GetPosition(), tile->GetScale());
		}
	}
}

void TowerManager::ClearTowers()
{
	for (const auto& tile : towers)
	{
		tile->Disable();
	}
}
#pragma endregion ManageTowers

#pragma region Get
TowerBase* TowerManager::GetInactiveTowerOfType(BulletType bulletType)
{
	for (const auto& tower : towers)
	{
		if (tower->GetType() == bulletType)
		{
			if (tower->IsActive() == false)
			{
				return tower;
			}
		}
	}
	std::cout << "Could not find an tower that is inactive, returning nullptr" << std::endl;
	return nullptr;
}
#pragma endregion Get