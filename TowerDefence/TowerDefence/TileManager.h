#pragma once
#include <vector>
#include "Tile.h"

class MapManager;

class TileManager
{
private:
	std::vector<Tile*> tiles;

public:

private:

public:
	void AddTile(Tile* tile);
	Tile* GetTile(SpriteName spriteName);
	std::vector<Tile*> GetTiles(SpriteName spriteName);
	std::vector<Tile*> GetTilesList() { return tiles; }
	std::vector<Tile*> GetWalkableTiles();
	std::vector<Tile*> GetWalkableNeighboursOfTile(Tile* tile);
	Tile* GetTileAtPosition(Vector2D position);
	int GetTileIndexInList(Tile* tile);

	void Start();
	void Update();
	void Render();
	void Destroy();

	void DebugPositions();
	void CreateTilesFromMap(MapManager* mapManager, int mapIndex);
};