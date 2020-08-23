#pragma once
#include <vector>
#include <SDL.h>
#include "Enemy.h"
#include "Dijkstra.h"
#include "IRenderable.h"
#include "ManagerBase.h"
#include "Managers.h"
#include "MapManager.h"
#include "LevelManager.h"
#include "TileManager.h"
#include "SpriteManager.h"

class EnemyManager : public IRenderable, public ManagerBase
{
private:
	std::vector<Enemy*> enemies;
	Dijkstra* dijkstra = nullptr;
	Managers* managers = nullptr;
	MapManager* mapManager = nullptr;
	LevelManager* levelManager = nullptr;
	TileManager* tileManager = nullptr;
	SpriteManager* spriteManager = nullptr;

	//For creating enemies
	std::vector<Tile*> path;
	std::vector<std::vector<int>> mapEnemyNumbers;
	int enemyIndex = 0;
	int spawnIndex = 0;
	int waveIndex = 0;

	//For numbers in level
	int enemyCount = 0;
	int enemyDeathCount = 0;

	//For spawning enemies
	float spawnTimer = 0;
	float maxSpawnTime = 1.0f;
	float maxWaveTime = 5.0f;
	bool waveIsComplete = false;
	bool mapIsComplete = false;

	//Enemy attributes
	//EnemySmall
	std::string ES_name = "EnemySmall";
	SpriteName ES_spriteName = SpriteName::SmallEnemy;
	float ES_health = 3.0f;
	//EnemyBig
	std::string EB_name = "EnemyBig";
	SpriteName EB_spriteName = SpriteName::BigEnemy;
	float EB_health = 10.0f;


private:
	void CreateEnemy(int waveIndex, int enemyIndex);
	void SetEnemyCountFromMap();
	void ResetEnemyCount();

public:
	EnemyManager(Dijkstra* dijkstra);
	~EnemyManager();

	void IncreaseEnemyDeathCount(int increaseBy);
	void SpawnEnemyWaves(float deltaTime);

	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Destroy() override;

	void CreateEnemies();
	void ClearEnemies();
	void DebugPositions();

	Enemy* GetInactiveEnemy();
	std::vector<Enemy*> GetEnemies() { return enemies; }
};