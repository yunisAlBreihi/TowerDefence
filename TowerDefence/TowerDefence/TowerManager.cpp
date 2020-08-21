#include "TowerManager.h"
#include "TowerSmall.h"
#include "TowerBig.h"

TowerManager::TowerManager(Managers* managers) : managers(managers)
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
	for (const auto& t : towers)
	{
		t->Start();
	}
}

void TowerManager::Update(float deltaTime)
{
	for (const auto& t : towers)
	{
		t->Update(deltaTime);
	}
}

void TowerManager::Render()
{
	for (const auto& t : towers)
	{
		t->Render();
	}
}

void TowerManager::Destroy()
{
	for (const auto& t : towers)
	{
		t->Destroy();
	}
}

void TowerManager::CreateTower(Sprite* sprite, Vector2D position, Vector2D scale)
{
	if (sprite->GetSpriteName() == SpriteName::TowerSmall)
	{
		TowerSmall* towerSmall = (TowerSmall*)GetInactiveTowerOfType(BulletType::Regular);
		if (towerSmall == nullptr)
		{
			towerSmall = new TowerSmall(managers, BulletType::Regular, sprite, position, scale);
			towers.push_back(towerSmall);
		}
		else
		{
			towerSmall->Reset(managers, BulletType::Regular, sprite, position, scale);
		}
	}
	else if (sprite->GetSpriteName() == SpriteName::TowerBig)
	{
		TowerBig* towerBig = (TowerBig*)GetInactiveTowerOfType(BulletType::Freezing);
		if (towerBig == nullptr)
		{
			towerBig = new TowerBig(managers, BulletType::Freezing, sprite, position, scale);
			towers.push_back(towerBig);
		}
		else
		{
			towerBig->Reset(managers, BulletType::Freezing, sprite, position, scale);
		}
	}
}

void TowerManager::CreateTowers()
{
	Sprite* sprite = nullptr;
	for (Tile* tile : tileManager->GetTiles(SpriteName::Tower01))
	{
		if (tile->IsActive() == true)
		{
			sprite = spriteManager->GetSprite(SpriteName::TowerSmall);
			CreateTower(sprite, tile->GetPosition(), tile->GetScale());
		}
	}

	for (Tile* tile : tileManager->GetTiles(SpriteName::Tower02))
	{
		if (tile->IsActive() == true)
		{
			sprite = spriteManager->GetSprite(SpriteName::TowerBig);
			CreateTower(sprite, tile->GetPosition(), tile->GetScale());
		}
	}
}

void TowerManager::ClearTowers()
{
	for (TowerBase* t : towers)
	{
		t->Disable();
	}
}

TowerBase* TowerManager::GetInactiveTowerOfType(BulletType bulletType)
{
	for (auto tower : towers)
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