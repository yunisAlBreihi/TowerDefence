#pragma once
#include <vector>
#include "EnemyBase.h"
#include "Dijkstra.h"
#include "MapManager.h"
#include "IRenderable.h"
#include "ManagerBase.h"
#include "Managers.h"

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
	std::vector<Tile*> path;
	std::vector<std::vector<int>> mapEnemyNumbers;
	int enemyIndex = 0;
	int spawnIndex = 0;
	int waveIndex = 0;
	int enemyCount = 0;
	int enemyDeathCount = 0;
	float spawnTimer = 0;
	float maxSpawnTime = 2000;
	float maxWaveTime = 10000;
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

	void DebugPositions();
	EnemyBase* GetEnemyTypeAtIndex(EnemyType enemyType, int index);
	std::vector<std::vector<EnemyBase*>> GetEnemies() { return enemies; }
};