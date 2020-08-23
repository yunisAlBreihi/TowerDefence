#include "LevelManager.h"
#include "TileManager.h"
#include "TowerManager.h"
#include "UIManager.h"
#include "GameManager.h"

#pragma region Construction
LevelManager::LevelManager()
{
	managers = Managers::GetInstance();
	name = ManagerName::LevelManager;
	mapManager = managers->GetManager<MapManager>(ManagerName::MapManager);
}

LevelManager::~LevelManager()
{
}
#pragma endregion Construction

#pragma region GameLoop
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
#pragma endregion GameLoop

#pragma region ChangeScreenObjects
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

	EffectManager* effectsManager = managers->GetManager<EffectManager>(ManagerName::EffectsManager);
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
#pragma endregion ChangeScreenObjects

#pragma region LevelLoading
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
	managers->GetManager<UIManager>(ManagerName::UIManager)->Congratulations(true);
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
	managers->GetManager<UIManager>(ManagerName::UIManager)->GameOver(true);
	managers->GetManager<GameManager>(ManagerName::GameManager)->SetGameHasEnded(true);
	loadGameOver = false;
}
#pragma endregion LevelLoading