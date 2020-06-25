#pragma once
#include "Tile.h"
#include <vector>

class TileManager
{
private:
	std::vector<Tile*> tileList;

public:

private:

public:
	void AddTile(Tile* tile);

	void Start();
	void Update();
	void Render();
	void Destroy();

	void DebugPositions();
};
