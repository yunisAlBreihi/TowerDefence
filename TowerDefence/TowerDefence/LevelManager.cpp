#include "LevelManager.h"
#include "TileManager.h"
#include "TowerManager.h"
#include "UIManager.h"
#include "GameManager.h"

LevelManager::LevelManager(Managers* managers) : managers(managers)
{
	name = ManagerName::LevelManager;
	mapManager = managers->GetManager<MapManager>(ManagerName::MapManager);
}

LevelManager::~LevelManager()
{

}

void LevelManager::Start()
{
	LoadCurrentLevel();
}

void LevelManager::Update(float deltaTime)
{
	if (loadNextLevel == true)
	{
		OnLoadNextLevel();
	}
	else if (loadGameOver == true)
	{
		OnLoadGameOverScreen();
	}
	else if (loadCongratulations == true)
	{
		OnLoadCongratulationsSceen();
	}
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

	BulletManager* bulletManager = managers->GetManager<BulletManager>(ManagerName::BulletManager);
	bulletManager->ClearBullets();

	EffectsManager* effectsManager = managers->GetManager<EffectsManager>(ManagerName::EffectsManager);
	effectsManager->ClearEffects();
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
	currentLevelIndex += 1;
	if (currentLevelIndex >= mapManager->GetMaps().size())
	{
		LoadCongratulationsSceen();
		loadNextLevel = false;
	}
	else
	{
		LoadCurrentLevel();
		loadNextLevel = false;
	}
}

void LevelManager::LoadCongratulationsSceen()
{
	loadCongratulations = true;
}

void LevelManager::OnLoadCongratulationsSceen()
{
	ClearScreen();
	managers->GetManager<UIManager>(ManagerName::UIManager)->SetCongratulationsScreenVisibility(true);
	managers->GetManager<GameManager>(ManagerName::GameManager)->SetGameHasEnded(true);
	loadCongratulations = false;
}

void LevelManager::LoadGameOverScreen()
{
	loadGameOver = true;
}

void LevelManager::OnLoadGameOverScreen()
{
	ClearScreen();
	managers->GetManager<UIManager>(ManagerName::UIManager)->SetGameOverScreenVisibility(true);
	managers->GetManager<GameManager>(ManagerName::GameManager)->SetGameHasEnded(true);
	loadGameOver = false;
}
