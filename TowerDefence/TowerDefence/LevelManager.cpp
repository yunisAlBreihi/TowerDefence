#include "LevelManager.h"
#include "TileManager.h"

void LevelManager::Start()
{
	((TileManager*)managers->GetManager(ManagerName::TileManager))->CreateTilesFromMap(managers, currentLevelIndex);
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

LevelManager::LevelManager(Managers* managers) : managers(managers)
{
	name = ManagerName::LevelManager;
}

LevelManager::~LevelManager()
{
}

void LevelManager::LoadCurrentLevel()
{
}
