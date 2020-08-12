#include "LevelManager.h"
#include "TileManager.h"
#include "TowerManager.h"

LevelManager::LevelManager(Managers* managers) : managers(managers)
{
	name = ManagerName::LevelManager;
}

LevelManager::~LevelManager()
{

}

void LevelManager::Start()
{
	LoadCurrentLevel();
}

void LevelManager::Update()
{
}

void LevelManager::Render()
{
}

void LevelManager::Destroy()
{
}

void LevelManager::LoadCurrentLevel()
{
	TileManager* tileManager = ((TileManager*)managers->GetManager(ManagerName::TileManager));
	tileManager->ClearTiles();
	tileManager->CreateTilesFromMap(managers, currentLevelIndex);

	TowerManager* towerManager = ((TowerManager*)managers->GetManager(ManagerName::TowerManager));
	towerManager->ClearTowers();
	towerManager->CreateTowers();

	EnemyManager* enemyManager = ((EnemyManager*)managers->GetManager(ManagerName::EnemyManager));
	enemyManager->ClearEnemies();
	enemyManager->CreateEnemies();
}

void LevelManager::LoadNextLevel()
{
	currentLevelIndex += 1;
	LoadCurrentLevel();
}
