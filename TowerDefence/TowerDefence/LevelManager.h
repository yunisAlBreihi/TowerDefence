#pragma once
#include "ManagerBase.h"
#include "IRenderable.h"
#include "Managers.h"

class LevelManager : public IRenderable ,public ManagerBase
{
private:
	Managers* managers = nullptr;
	int currentLevelIndex = 0;
	bool loadNextLevel = false;
	//bool showGameOverScreen = false;
	//bool showCongratulationsScreen = false;
public:

private:
	void OnLoadNextLevel();

public:
	LevelManager(Managers* managers);
	~LevelManager();

	void Start() override;
	void Update() override;
	void Render() override;
	void Destroy() override;

	void ClearScreen();
	void CreateScreen();
	void LoadCurrentLevel();
	void LoadNextLevel();
	void LoadCongratulationsSceen();
	int GetCurrentLevelIndex() { return currentLevelIndex; }
	bool GetLoadNextLevel() { return loadNextLevel; }
};