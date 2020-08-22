#include "EnemyManager.h"
#include "Enemy.h"
#include "Globals.h"

EnemyManager::EnemyManager(Dijkstra* dijkstra) : dijkstra(dijkstra)
{
	managers = Managers::GetInstance();
	name = ManagerName::EnemyManager;
	mapManager = managers->GetManager<MapManager>(ManagerName::MapManager);
	levelManager = managers->GetManager<LevelManager>(ManagerName::LevelManager);
	tileManager = managers->GetManager<TileManager>(ManagerName::TileManager);
}

void EnemyManager::Start()
{
	CreateEnemies();

	for (Enemy* enemy : enemies)
	{
		enemy->Start();
	}
}

void EnemyManager::Update(float deltaTime)
{
	SpawnEnemyWaves(deltaTime);

	for (Enemy* enemy : enemies)
	{
		enemy->Update(deltaTime);
	}
}

void EnemyManager::Render()
{
	for (Enemy* enemy : enemies)
	{
		enemy->Render();
	}
}

void EnemyManager::Destroy()
{
	for (Enemy* enemy : enemies)
	{
		enemy->Destroy();
	}
}

void EnemyManager::CreateEnemies()
{
	path = dijkstra->FindShortestPath(tileManager, tileManager->GetTile(SpriteName::StartPosition), tileManager->GetTile(SpriteName::EndPosition));

	LevelManager* levelManager = managers->GetManager<LevelManager>(ManagerName::LevelManager);

	mapEnemyNumbers = mapManager->GetMap(levelManager->GetCurrentLevelIndex())->GetEnemyNumbers();

	SetEnemyCountFromMap();
}

void EnemyManager::ClearEnemies()
{
	for (Enemy* enemy : enemies)
	{
		if (enemy->IsActive() == true)
		{
			enemy->Disable();
		}
	}
}

void EnemyManager::DebugPositions()
{
	for (Enemy* enemy : enemies)
	{
		std::cout << "X position: " << enemy->GetPosition().x << " Y position: " << enemy->GetPosition().y << std::endl;
	}
}

Enemy* EnemyManager::GetInactiveEnemy()
{
	for (Enemy* enemy : enemies)
	{
		if (enemy->IsActive() == false)
		{
			return enemy;
		}
	}
	std::cout << "Could not find an enemy that is inactive, returning nullptr" << std::endl;
	return nullptr;

}

void EnemyManager::AddEnemyType(Sprite* enemySprite)
{
	sprites.push_back(enemySprite);
}

void EnemyManager::IncreaseEnemyDeathCount(int increaseBy)
{
	enemyDeathCount += increaseBy;
	//TODO: Change to enemyCount instead of a hard number
	if (enemyDeathCount == levelManager->GetKillsToNextLevel())
	{
		levelManager->LoadNextLevel();
	}
}

void EnemyManager::CreateEnemy(int waveIndex, int enemyIndex)
{
	Enemy* enemy = GetInactiveEnemy();

	//If didn't find an inactive enemy, create a new one
	if (enemy == nullptr)
	{
		if (enemyIndex == (int)EnemyType::SmallEnemy)
		{
			enemy = new Enemy(managers, path, "SmallEnemy" + std::to_string(waveIndex) + "-" + std::to_string(enemyIndex), sprites[enemyIndex],
				tileManager->GetTile(SpriteName::StartPosition)->GetPosition(), Vector2D(Globals::DEFAULT_SPRITE_SIZE, Globals::DEFAULT_SPRITE_SIZE), 3.0f);

		}
		else if (enemyIndex == (int)EnemyType::BigEnemy)
		{
			enemy = new Enemy(managers, path, "BigEnemy" + std::to_string(waveIndex) + "-" + std::to_string(enemyIndex), sprites[enemyIndex],
				tileManager->GetTile(SpriteName::StartPosition)->GetPosition(), Vector2D(Globals::DEFAULT_SPRITE_SIZE, Globals::DEFAULT_SPRITE_SIZE), 10.0f);
		}
		enemies.push_back(enemy);
	}
	else
	{
		if (enemyIndex == (int)EnemyType::SmallEnemy)
		{
			enemy->Reset(managers, path, "SmallEnemy" + std::to_string(waveIndex) + "-" + std::to_string(enemyIndex), sprites[enemyIndex],
				tileManager->GetTile(SpriteName::StartPosition)->GetPosition(), Vector2D(Globals::DEFAULT_SPRITE_SIZE, Globals::DEFAULT_SPRITE_SIZE), 3.0f);
		}
		else if (enemyIndex == (int)EnemyType::BigEnemy)
		{
			enemy->Reset(managers, path, "BigEnemy" + std::to_string(waveIndex) + "-" + std::to_string(enemyIndex), sprites[enemyIndex],
				tileManager->GetTile(SpriteName::StartPosition)->GetPosition(), Vector2D(Globals::DEFAULT_SPRITE_SIZE, Globals::DEFAULT_SPRITE_SIZE), 10.0f);
		}

	}
	enemy->Start();
}

void EnemyManager::SetEnemyCountFromMap()
{
	ResetEnemyCount();
	for (std::vector<int> enemyType : mapEnemyNumbers)
	{
		for (int enemyNumbers : enemyType)
		{
			enemyCount += enemyNumbers;
		}
	}
}

void EnemyManager::ResetEnemyCount()
{
	enemyCount = 0;
	enemyDeathCount = 0;
	mapIsComplete = false;
	waveIsComplete = false;
	waveIndex = 0;
	enemyIndex = 0;
	spawnIndex = 0;
	spawnTimer = 0;
}

void EnemyManager::SpawnEnemyWaves(float deltaTime)
{
	if (mapIsComplete == false)
	{
		spawnTimer += deltaTime;
		if (waveIsComplete == false)
		{
			if (spawnTimer >= maxSpawnTime)
			{
				if (mapEnemyNumbers[waveIndex][enemyIndex] > 0)
				{
					CreateEnemy(waveIndex, enemyIndex);
				}
				spawnIndex += 1;

				if (spawnIndex >= mapEnemyNumbers[waveIndex][enemyIndex])
				{
					enemyIndex += 1;
					spawnIndex = 0;
				}

				if (enemyIndex > mapEnemyNumbers[waveIndex].size() - 1)
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