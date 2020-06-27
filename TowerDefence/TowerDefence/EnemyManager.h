#pragma once
#include <vector>
#include "EnemyBase.h"

class EnemyManager
{
private:
	std::vector<EnemyBase*> enemies;

public:

private:

public:
	void AddEnemy(EnemyBase* enemy);

	void Start();
	void Update();
	void Render();
	void Destroy();

	void DebugPositions();
};