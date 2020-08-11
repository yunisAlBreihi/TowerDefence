#pragma once
#include "ManagerBase.h"
#include "IRenderable.h"
#include "Managers.h"

class LevelManager : public IRenderable ,public ManagerBase
{
private:
	Managers* managers = nullptr;
	int currentLevelIndex = 0;
public:

private:
public:
	LevelManager(Managers* managers);
	~LevelManager();

	void Start() override;
	void Update() override;
	void Render() override;
	void Destroy() override;

	void LoadCurrentLevel();
};