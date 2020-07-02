#pragma once
#include <vector>
#include "EnemyBase.h"
#include "Dijkstra.h"


class SDL_Renderer;

class EnemyManager
{
private:
	std::vector<EnemyBase*> enemies;
	SDL_Renderer* renderer;
	Dijkstra* dijkstra = nullptr;
	TileManager* tileManager = nullptr;
	std::vector<Tile*> path;
	int pathIndex = 0;

public:

private:

public:
	EnemyManager(SDL_Renderer* renderer, TileManager* tileManager, Dijkstra* dijkstra);

	void AddEnemy(EnemyBase* enemy);

	void Start();
	void Update();
	void Render();
	void Destroy();

	void DebugPositions();
};