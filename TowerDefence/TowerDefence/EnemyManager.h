#pragma once
#include <vector>
#include "EnemyBase.h"
#include "Dijkstra.h"
#include "IRenderable.h"
#include "ManagerBase.h"
#include "Managers.h"
#include "MapManager.h"
#include "LevelManager.h"
#include "TileManager.h"

class SDL_Renderer;

class EnemyManager : public IRenderable, public ManagerBase
{
private:
	std::vector<Sprite*> sprites;
	std::vector<std::vector<EnemyBase*>> enemies;
	Dijkstra* dijkstra = nullptr;
	Managers* managers = nullptr;
	MapManager* mapManager = nullptr;
	LevelManager* levelManager = nullptr;
	TileManager* tileManager = nullptr;
	std::vector<Tile*> path;
	std::vector<std::vector<int>> mapEnemyNumbers;
	int enemyIndex = 0;
	int spawnIndex = 0;
	int waveIndex = 0;
	int enemyCount = 0;
	int enemyDeathCount = 0;
	float spawnTimer = 0;
	float maxSpawnTime = 1.0f;
	float maxWaveTime = 5.0f;
	bool waveIsComplete = false;
	bool mapIsComplete = false;
public:
private:

	EnemyBase* CreateEnemy(Sprite* enemySprite, int waveIndex, int enemyIndex);
	void SetEnemyCountFromMap();
	void ResetEnemyCount();

public:
	EnemyManager(Managers* managers, Dijkstra* dijkstra);

	void AddEnemyType(Sprite* enemySprite);
	void IncreaseEnemyDeathCount(int increaseBy);
	void SpawnEnemyWaves(float deltaTime);

	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Destroy() override;

	void CreateEnemies();
	void ClearEnemies();
	void DebugPositions();

	EnemyBase* GetInactiveEnemyOfType(EnemyType enemyType);

	EnemyBase* GetEnemyTypeAtIndex(EnemyType enemyType, int index);
	std::vector<std::vector<EnemyBase*>> GetEnemies() { return enemies; }
};