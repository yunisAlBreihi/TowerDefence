#include "EnemyManager.h"

void EnemyManager::Start()
{
}

void EnemyManager::Update()
{
}

void EnemyManager::Render()
{
	for (EnemyBase* e : enemies)
	{
		e->Render();
	}
}

void EnemyManager::Destroy()
{
	for (EnemyBase* e : enemies)
	{
		e->Destroy();
	}
}

void EnemyManager::DebugPositions()
{
	for (EnemyBase* e : enemies)
	{
		std::cout << "X position: " << e->GetPosition().x << " Y position: " << e->GetPosition().y << std::endl;
	}
}

void EnemyManager::AddEnemy(EnemyBase* enemy)
{
	enemies.push_back(enemy);
}
