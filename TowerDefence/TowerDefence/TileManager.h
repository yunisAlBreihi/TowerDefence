#pragma once
#include <vector>
#include "Tile.h"

class TileManager
{
private:
	std::vector<Tile*> tiles;

public:

private:

public:
	void AddTile(Tile* tile);
	Tile* GetTile(SpriteName spriteName);

	void Start();
	void Update();
	void Render();
	void Destroy();

	void DebugPositions();
};
