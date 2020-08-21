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
	int currentLevelIndex = 0;
	bool loadNextLevel = false;
	bool loadGameOver = false;
	bool loadCongratulations = false;
public:
	//TODO: only for debug, remove
	int levelChange = 0;
private:
	void OnLoadNextLevel();
	void OnLoadCongratulationsSceen();
	void OnLoadGameOverScreen();

public:
	LevelManager();
	~LevelManager();

	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Destroy() override;

	void ClearScreen();
	void CreateScreen();
	void LoadCurrentLevel();
	void LoadNextLevel();
	void LoadCongratulationsSceen();
	void LoadGameOverScreen();
	int GetCurrentLevelIndex() { return currentLevelIndex; }
	bool GetLoadNextLevel() { return loadNextLevel; }
};