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
	enemies.push_back(std::vector<Enemy*>());
	enemies.push_back(std::vector<Enemy*>());

	if (enemies.empty() == false)
	{
		for (const auto& enemyRow : enemies)
		{
			if (enemyRow.empty() == false)
			{
				for (Enemy* e : enemyRow)
				{
					e->Start();
				}
			}
		}
	}
}

void EnemyManager::Update(float deltaTime)
{
	SpawnEnemyWaves(deltaTime);

	if (enemies.empty() == false)
	{
		for (const auto& enemyRow : enemies)
		{
			if (enemyRow.empty() == false)
			{
				for (Enemy* e : enemyRow)
				{
					e->Update(deltaTime);
				}
			}
		}
	}
}

void EnemyManager::Render()
{
	if (enemies.size() != 0)
	{
		for (const auto& enemyRow : enemies)
		{
			if (enemyRow.empty() == false)
			{
				for (Enemy* e : enemyRow)
				{
					e->Render();
				}
			}
		}
	}
}

void EnemyManager::Destroy()
{
	for (const auto& enemyRow : enemies)
	{
		for (Enemy* e : enemyRow)
		{
			e->Destroy();
		}
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
	for (auto enemyRow : enemies)
	{
		for (auto e : enemyRow)
		{
			e->Disable();
		}
	}
}

void EnemyManager::DebugPositions()
{
	for (const auto& enemyRow : enemies)
	{
		for (Enemy* e : enemyRow)
		{
			std::cout << "X position: " << e->GetPosition().x << " Y position: " << e->GetPosition().y << std::endl;
		}
	}
}

Enemy* EnemyManager::GetInactiveEnemyOfType(EnemyType enemyType)
{
	for (auto enemy : enemies[(int)enemyType])
	{
		if (enemy->IsActive() == false)
		{
			return enemy;
		}
	}
	std::cout << "Could not find an enemy that is inactive, returning nullptr" << std::endl;
	return nullptr;

}

Enemy* EnemyManager::GetEnemyTypeAtIndex(EnemyType enemyType, int index)
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
	//TODO: Change to enemyCount instead of a hard number
	if (enemyDeathCount == 21)
	{
		managers->GetManager<LevelManager>(ManagerName::LevelManager)->LoadNextLevel();
	}
}

Enemy* EnemyManager::CreateEnemy(Sprite* enemySprite, int waveIndex, int enemyIndex)
{
	Enemy* enemy = GetInactiveEnemyOfType(EnemyType::SmallEnemy);
	
	if (enemySprite->GetSpriteName() == SpriteName::EnemySmall)
	{
		Enemy* enemy = new Enemy(managers, path, "EnemySmall" + std::to_string(waveIndex) + "-" + std::to_string(enemyIndex), sprites[0],
			tileManager->GetTile(SpriteName::StartPosition)->GetPosition(), Vector2D(Globals::DEFAULT_SPRITE_SIZE, Globals::DEFAULT_SPRITE_SIZE), 3.0f);
		enemy->Start();
		return enemy;
	}
	else if (enemySprite->GetSpriteName() == SpriteName::EnemyBig)
	{
		Enemy* enemy = new Enemy(managers, path, "EnemyBig" + std::to_string(waveIndex) + "-" + std::to_string(enemyIndex), sprites[1],
			tileManager->GetTile(SpriteName::StartPosition)->GetPosition(), Vector2D(Globals::DEFAULT_SPRITE_SIZE, Globals::DEFAULT_SPRITE_SIZE), 10.0f);
		enemy->Start();
		return enemy;
	}
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
					//If there is already a created Inactive enemy, get that one. else create a new one
					Enemy* enemy = nullptr;
					if (enemyIndex == 0)
					{
						enemy = GetInactiveEnemyOfType(EnemyType::BigEnemy);
						if (enemy != nullptr)
						{
							enemy->Reset(managers, path, "EnemySmall" + std::to_string(waveIndex) + "-" + std::to_string(enemyIndex), sprites[0],
								tileManager->GetTile(SpriteName::StartPosition)->GetPosition(), Vector2D(Globals::DEFAULT_SPRITE_SIZE, Globals::DEFAULT_SPRITE_SIZE), 3.0f);
							enemy->Start();
						}
						else
						{
							enemy = CreateEnemy(sprites[enemyIndex], waveIndex, spawnIndex);
							enemies[enemyIndex].push_back(enemy);
						}
					}
					else if (enemyIndex == 1)
					{
						enemy = GetInactiveEnemyOfType(EnemyType::BigEnemy);
						if (enemy != nullptr)
						{
							enemy->Reset(managers, path, "EnemyBig" + std::to_string(waveIndex) + "-" + std::to_string(enemyIndex), sprites[1],
								tileManager->GetTile(SpriteName::StartPosition)->GetPosition(), Vector2D(Globals::DEFAULT_SPRITE_SIZE, Globals::DEFAULT_SPRITE_SIZE), 10.0f);
							enemy->Start();
						}
						else
						{
							enemy = CreateEnemy(sprites[enemyIndex], waveIndex, spawnIndex);
							enemies[enemyIndex].push_back(enemy);
						}
					}
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