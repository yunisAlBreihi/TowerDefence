#include "EnemyManager.h"
#include "TileManager.h"
#include "GameManager.h"
#include "EnemySmall.h"
#include "EnemyBig.h"

EnemyManager::EnemyManager(SDL_Renderer* renderer, TileManager* tileManager, MapManager* mapManager, Dijkstra* dijkstra) : renderer(renderer), tileManager(tileManager), mapManager(mapManager), dijkstra(dijkstra)
{
}

void EnemyManager::Start()
{
	path = dijkstra->FindShortestPath(tileManager, tileManager->GetTile(SpriteName::startPosition), tileManager->GetTile(SpriteName::endPosition));

	mapEnemyNumbers = mapManager->GetMap(1)->GetEnemyNumbers();
	enemies.push_back(std::vector<EnemyBase*>());
	enemies.push_back(std::vector<EnemyBase*>());

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

void EnemyManager::AddEnemy(Sprite* enemySprite)
{
	sprites.push_back(enemySprite);
}

EnemyBase* EnemyManager::CreateEnemy(Sprite* enemySprite)
{
	if (enemySprite->GetSpriteName() == SpriteName::EnemySmall)
	{
		EnemySmall* enemy = new EnemySmall(renderer, path, sprites[0], tileManager->GetTile(SpriteName::startPosition)->GetPosition(), Vector2D(GameManager::DEFAULT_SPRITE_SIZE, GameManager::DEFAULT_SPRITE_SIZE));
		return enemy;
	}
	else if (enemySprite->GetSpriteName() == SpriteName::EnemyBig)
	{
		EnemyBig* enemy = new EnemyBig(renderer, path, sprites[1], tileManager->GetTile(SpriteName::startPosition)->GetPosition(), Vector2D(GameManager::DEFAULT_SPRITE_SIZE, GameManager::DEFAULT_SPRITE_SIZE));
		return enemy;
	}
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