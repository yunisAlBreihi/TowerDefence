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

enum class EnemyType
{
	smallEnemy,
	bigEnemy,
};

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
	float maxSpawnTime = 1000;
	float maxWaveTime = 5000;
	bool waveIsComplete = false;
	bool mapIsComplete = false;

public:

private:

	EnemyBase* CreateEnemy(Sprite* enemySprite);
	void SetEnemyCountFromMap();
	void ResetEnemyCount();

public:
	EnemyManager(Managers* managers, Dijkstra* dijkstra);

	void AddEnemyType(Sprite* enemySprite);
	void IncreaseEnemyDeathCount(int increaseBy);
	void SpawnEnemyWaves();

	void Start() override;
	void Update() override;
	void Render() override;
	void Destroy() override;

	void CreateEnemies();
	void ClearEnemies();
	void DebugPositions();

	EnemyBase* GetEnemyTypeAtIndex(EnemyType enemyType, int index);
	std::vector<std::vector<EnemyBase*>> GetEnemies() { return enemies; }
};