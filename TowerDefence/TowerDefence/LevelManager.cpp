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

void LevelManager::ShowGameOverScreen()
{
}

void LevelManager::ShowCongratulationsScreen()
{
}

void LevelManager::ClearScreen()
{
	TileManager* tileManager = ((TileManager*)managers->GetManager(ManagerName::TileManager));
	tileManager->ClearTiles();

	TowerManager* towerManager = ((TowerManager*)managers->GetManager(ManagerName::TowerManager));
	towerManager->ClearTowers();

	EnemyManager* enemyManager = ((EnemyManager*)managers->GetManager(ManagerName::EnemyManager));
	enemyManager->ClearEnemies();
}

void LevelManager::CreateScreen()
{
	TileManager* tileManager = ((TileManager*)managers->GetManager(ManagerName::TileManager));
	tileManager->CreateTilesFromMap(managers, currentLevelIndex);

	TowerManager* towerManager = ((TowerManager*)managers->GetManager(ManagerName::TowerManager));
	towerManager->CreateTowers();

	EnemyManager* enemyManager = ((EnemyManager*)managers->GetManager(ManagerName::EnemyManager));
	enemyManager->CreateEnemies();
}

void LevelManager::LoadCurrentLevel()
{
	ClearScreen();
	CreateScreen();
}

void LevelManager::LoadNextLevel()
{
	currentLevelIndex += 1;
	LoadCurrentLevel();
}
