#include "EnemyManager.h"
#include "Enemy.h"
#include "Globals.h"

#pragma region Construction
EnemyManager::EnemyManager(Dijkstra* dijkstra) : dijkstra(dijkstra)
{
	managers = Managers::GetInstance();
	name = ManagerName::EnemyManager;
	mapManager = managers->GetManager<MapManager>(ManagerName::MapManager);
	levelManager = managers->GetManager<LevelManager>(ManagerName::LevelManager);
	tileManager = managers->GetManager<TileManager>(ManagerName::TileManager);
	spriteManager = managers->GetManager<SpriteManager>(ManagerName::SpriteManager);
}

EnemyManager::~EnemyManager()
{
}
#pragma endregion Construction

#pragma region GameLoop
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
#pragma endregion GameLoop



#pragma region Disable
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
#pragma endregion Disable



void EnemyManager::IncreaseEnemyDeathCount(int increaseBy)
{
	enemyDeathCount += increaseBy;
	//TODO: Change to enemyCount instead of a hard number
	if (enemyDeathCount == levelManager->GetKillsToNextLevel())
	{
		levelManager->LoadNextLevel();
	}
}

#pragma region Create
void EnemyManager::CreateEnemies()
{
	path = dijkstra->FindShortestPath(tileManager->GetTileWithSprite(SpriteName::EnemyBase), tileManager->GetTileWithSprite(SpriteName::PlayerBase));

	LevelManager* levelManager = managers->GetManager<LevelManager>(ManagerName::LevelManager);

	mapEnemyNumbers = mapManager->GetMapAtIndex(levelManager->GetCurrentLevelIndex())->GetEnemyNumbers();

	SetEnemyCountFromMap();
}

void EnemyManager::CreateEnemy(int waveIndex, int enemyIndex)
{
	Enemy* enemy = GetInactiveEnemy();

	std::string nameEnding = std::to_string(waveIndex) + "-" + std::to_string(enemyIndex);
	Vector2D tempPosition = tileManager->GetTileWithSprite(SpriteName::EnemyBase)->GetPosition();
	Vector2D tempScale = Vector2D(Globals::DEFAULT_SPRITE_SIZE, Globals::DEFAULT_SPRITE_SIZE);

	if (enemyIndex == (int)EnemyType::EnemySmall)
	{
		//If there are no inactive enemies, create a new one
		if (enemy == nullptr)
		{
			enemy = new Enemy(managers, path, ES_name + nameEnding, spriteManager->GetSprite(ES_spriteName), tempPosition, tempScale, ES_health);
			enemies.push_back(enemy);
		}
		else
		{
			enemy->Reset(managers, path, ES_name + nameEnding, spriteManager->GetSprite(ES_spriteName), tempPosition, tempScale, ES_health);
		}

	}
	else if (enemyIndex == (int)EnemyType::EnemyBig)
	{
		//If there are no inactive enemies, create a new one
		if (enemy == nullptr)
		{
			enemy = new Enemy(managers, path, EB_name + nameEnding, spriteManager->GetSprite(SpriteName::BigEnemy), tempPosition, tempScale, EB_health);
			enemies.push_back(enemy);
		}
		else
		{
			enemy->Reset(managers, path, EB_name + nameEnding, spriteManager->GetSprite(SpriteName::BigEnemy), tempPosition, tempScale, EB_health);
		}
	}
	enemy->Start();
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
#pragma endregion Create

#pragma region GetSet
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
#pragma endregion GetSet

#pragma region Debug
void EnemyManager::DebugPositions()
{
	for (Enemy* enemy : enemies)
	{
		std::cout << "X position: " << enemy->GetPosition().x << " Y position: " << enemy->GetPosition().y << std::endl;
	}
}
#pragma endregion Debug