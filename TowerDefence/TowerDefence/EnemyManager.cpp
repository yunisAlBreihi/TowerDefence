#include "EnemyManager.h"
#include "GameManager.h"
#include "EnemySmall.h"
#include "EnemyBig.h"

EnemyManager::EnemyManager(Managers* managers, Dijkstra* dijkstra) : managers(managers), dijkstra(dijkstra)
{
	name = ManagerName::EnemyManager;
	mapManager = managers->GetManager<MapManager>(ManagerName::MapManager);
	levelManager = managers->GetManager<LevelManager>(ManagerName::LevelManager);
	tileManager = managers->GetManager<TileManager>(ManagerName::TileManager);
}

void EnemyManager::Start()
{

	CreateEnemies();
	if (enemies.empty() == false)
	{
		for (const auto& enemyRow : enemies)
		{
			if (enemyRow.empty() == false)
			{
				for (EnemyBase* e : enemyRow)
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
				for (EnemyBase* e : enemyRow)
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
				for (EnemyBase* e : enemyRow)
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
		for (EnemyBase* e : enemyRow)
		{
			e->Destroy();
		}
	}
}

void EnemyManager::CreateEnemies()
{
	path = dijkstra->FindShortestPath(tileManager, tileManager->GetTile(SpriteName::startPosition), tileManager->GetTile(SpriteName::endPosition));

	LevelManager* levelManager = managers->GetManager<LevelManager>(ManagerName::LevelManager);

	mapEnemyNumbers = mapManager->GetMap(levelManager->GetCurrentLevelIndex())->GetEnemyNumbers();
	enemies.push_back(std::vector<EnemyBase*>());
	enemies.push_back(std::vector<EnemyBase*>());

	SetEnemyCountFromMap();
}

void EnemyManager::ClearEnemies()
{
	//TODO: temp solution: destroy enemies
	if (enemies.empty() == false)
	{
		for (auto enemyRow : enemies)
		{
			for (auto e : enemyRow)
			{
				e->Destroy();
			}
		}
	}

	enemies.clear();
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
	//TODO: Change to enemyCount instead of a hard number
	if (enemyDeathCount == 20)
	{
		managers->GetManager<LevelManager>(ManagerName::LevelManager)->LoadNextLevel();
	}
}

EnemyBase* EnemyManager::CreateEnemy(Sprite* enemySprite, int num1, int num2)
{
	if (enemySprite->GetSpriteName() == SpriteName::EnemySmall)
	{
		EnemySmall* enemy = new EnemySmall(managers, path, "EnemySmall" + std::to_string(num1) + "-" +  std::to_string(num2), sprites[0], tileManager->GetTile(SpriteName::startPosition)->GetPosition(), Vector2D(GameManager::DEFAULT_SPRITE_SIZE, GameManager::DEFAULT_SPRITE_SIZE));
		enemy->Start();
		return enemy;
	}
	else if (enemySprite->GetSpriteName() == SpriteName::EnemyBig)
	{
		EnemyBig* enemy = new EnemyBig(managers, path, "EnemySmall" + std::to_string(num1) +"-" +std::to_string(num2), sprites[1], tileManager->GetTile(SpriteName::startPosition)->GetPosition(), Vector2D(GameManager::DEFAULT_SPRITE_SIZE, GameManager::DEFAULT_SPRITE_SIZE));
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
					enemies[enemyIndex].push_back(CreateEnemy(sprites[enemyIndex], waveIndex, spawnIndex));
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