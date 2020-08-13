#include "LevelManager.h"
#include "TileManager.h"
#include "TowerManager.h"
#include "UIManager.h"
#include "MapManager.h"

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
	OnLoadNextLevel();
}

void LevelManager::Render()
{
}

void LevelManager::Destroy()
{
}

void LevelManager::ClearScreen()
{
	TileManager* tileManager = managers->GetManager<TileManager>(ManagerName::TileManager);
	tileManager->ClearTiles();

	TowerManager* towerManager = managers->GetManager<TowerManager>(ManagerName::TowerManager);
	towerManager->ClearTowers();

	EnemyManager* enemyManager = managers->GetManager<EnemyManager>(ManagerName::EnemyManager);
	enemyManager->ClearEnemies();
}

void LevelManager::CreateScreen()
{
	TileManager* tileManager = managers->GetManager<TileManager>(ManagerName::TileManager);
	tileManager->CreateTilesFromMap(managers, currentLevelIndex);

	TowerManager* towerManager = managers->GetManager<TowerManager>(ManagerName::TowerManager);
	towerManager->CreateTowers();

	EnemyManager* enemyManager = managers->GetManager<EnemyManager>(ManagerName::EnemyManager);
	enemyManager->CreateEnemies();
}

void LevelManager::LoadCurrentLevel()
{
	ClearScreen();
	CreateScreen();
}

void LevelManager::LoadNextLevel()
{
	loadNextLevel = true;
}

void LevelManager::OnLoadNextLevel()
{
	if (loadNextLevel == true)
	{
		MapManager* mapManager = managers->GetManager<MapManager>(ManagerName::MapManager);
		currentLevelIndex += 1;
		if (currentLevelIndex >= mapManager->GetMaps().size())
		{
			LoadCongratulationsSceen();
		}
		else
		{
			LoadCurrentLevel();
		}
	}
}

void LevelManager::LoadCongratulationsSceen()
{
	ClearScreen();
	managers->GetManager<UIManager>(ManagerName::UIManager)->SetCongratulationsScreenVisibility(true);
}