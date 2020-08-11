#include "EnemyManager.h"
#include "GameManager.h"
#include "EnemySmall.h"
#include "EnemyBig.h"

EnemyManager::EnemyManager( Managers* managers, Dijkstra* dijkstra) :  managers(managers), dijkstra(dijkstra)
{
	name = ManagerName::EnemyManager;
}

void EnemyManager::Start()
{
	path = dijkstra->FindShortestPath((TileManager*)managers->GetManager(ManagerName::TileManager), ((TileManager*)managers->GetManager(ManagerName::TileManager))->GetTile(SpriteName::startPosition), ((TileManager*)managers->GetManager(ManagerName::TileManager))->GetTile(SpriteName::endPosition));

	MapManager* mapManager = ((MapManager*)managers->GetManager(ManagerName::MapManager));
	LevelManager* levelManager = ((LevelManager*)managers->GetManager(ManagerName::LevelManager));
	mapEnemyNumbers = mapManager->GetMap(1)->GetEnemyNumbers();

	enemies.push_back(std::vector<EnemyBase*>());
	enemies.push_back(std::vector<EnemyBase*>());

	SetEnemyCountFromMap();

	for (const auto& enemyRow : enemies)
	{
		for (EnemyBase* e : enemyRow)
		{
			e->Start();
		}
	}
}

void EnemyManager::Update()
{
	SpawnEnemyWaves();

	for (const auto& enemyRow : enemies)
	{
		for (EnemyBase* e : enemyRow)
		{
			e->Update();
		}
	}
}

void EnemyManager::Render()
{
	for (const auto& enemyRow : enemies)
	{
		for (EnemyBase* e : enemyRow)
		{
			e->Render();
		}
	}
}

void EnemyManager::Destroy()
{
	for (const auto& enemyRow : enemies)
	{
		for (EnemyBase* e : enemyRow)
		{
			e->Destroy();
		}
	}
}

void EnemyManager::DebugPositions()
{
	for (const auto& enemyRow : enemies)
	{
		for (EnemyBase* e : enemyRow)
		{
			std::cout << "X position: " << e->GetPosition().x << " Y position: " << e->GetPosition().y << std::endl;
		}
	}
}

EnemyBase* EnemyManager::GetEnemyTypeAtIndex(EnemyType enemyType, int index)
{
	return enemies[(int)enemyType][index];
}

void EnemyManager::AddEnemyType(Sprite* enemySprite)
{
	sprites.push_back(enemySprite);
}

void EnemyManager::IncreaseEnemyDeathCount(int increaseBy)
{
	enemyDeathCount += increaseBy;
}

EnemyBase* EnemyManager::CreateEnemy(Sprite* enemySprite)
{
	TileManager* tileManager = ((TileManager*)managers->GetManager(ManagerName::TileManager));
	if (enemySprite->GetSpriteName() == SpriteName::EnemySmall)
	{
		EnemySmall* enemy = new EnemySmall(managers->GetRenderer(), path, sprites[0], tileManager->GetTile(SpriteName::startPosition)->GetPosition(), Vector2D(GameManager::DEFAULT_SPRITE_SIZE, GameManager::DEFAULT_SPRITE_SIZE));
		enemy->Start();
		return enemy;
	}
	else if (enemySprite->GetSpriteName() == SpriteName::EnemyBig)
	{
		EnemyBig* enemy = new EnemyBig(managers->GetRenderer(), path, sprites[1], tileManager->GetTile(SpriteName::startPosition)->GetPosition(), Vector2D(GameManager::DEFAULT_SPRITE_SIZE, GameManager::DEFAULT_SPRITE_SIZE));
		enemy->Start();
		return enemy;
	}
}

void EnemyManager::SetEnemyCountFromMap()
{
	ResetEnemyCount();
	for (std::vector<int> enemyType : mapEnemyNumbers)
	{
		for (int enemy : enemyType)
		{
			enemyCount += 1;
		}
	}
	
}

void EnemyManager::ResetEnemyCount()
{
	enemyCount = 0;
	enemyDeathCount = 0;
}

void EnemyManager::SpawnEnemyWaves()
{
	if (mapIsComplete == false)
	{
		spawnTimer++;
		if (waveIsComplete == false)
		{
			if (spawnTimer >= maxSpawnTime)
			{
				if (mapEnemyNumbers[waveIndex][enemyIndex] > 0)
				{
					enemies[enemyIndex].push_back(CreateEnemy(sprites[enemyIndex]));
				}
				spawnIndex += 1;

				if (spawnIndex >= mapEnemyNumbers[waveIndex][enemyIndex])
				{
					enemyIndex += 1;
					spawnIndex = 0;
				}

				if (enemyIndex > enemies.size() - 1)
				{
					waveIsComplete = true;
					waveIndex += 1;
					enemyIndex = 0;
					if (waveIndex == mapEnemyNumbers.size())
					{
						mapIsComplete = true;
					}
				}
				spawnTimer = 0;
			}
		}
		else
		{
			if (spawnTimer >= maxWaveTime)
			{
				waveIsComplete = false;
			}
		}
	}
}