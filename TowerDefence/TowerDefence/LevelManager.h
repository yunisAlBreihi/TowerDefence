#pragma once
#include "ManagerBase.h"
#include "IRenderable.h"
#include "Managers.h"
#include "MapManager.h"

class LevelManager : public IRenderable, public ManagerBase
{
private:
	Managers* managers = nullptr;
	MapManager* mapManager = nullptr;

	//Level Attributes
	int KillsToChangeLevel = 20;
	int currentLevelIndex = 0;

	//For loading levels
	bool loadNextLevel = false;
	bool loadGameOver = false;
	bool loadCongratulations = false;

private:
	void OnLoadNextLevel();
	void OnLoadCongratulationsSceen();
	void OnLoadGameOverScreen();

	void ClearScreen();
	void CreateScreen();
	void LoadCurrentLevel();
	void LoadCongratulationsSceen();

public:
	LevelManager();

	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;

	void LoadNextLevel();
	void LoadGameOverScreen();

	int GetCurrentLevelIndex() { return currentLevelIndex; }
	int GetKillsToNextLevel() { return KillsToChangeLevel; }
	bool GetLoadNextLevel() { return loadNextLevel; }
};