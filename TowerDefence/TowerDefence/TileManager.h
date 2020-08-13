#pragma once
#include <vector>
#include "ManagerBase.h"
#include "Managers.h"
#include "Tile.h"
#include "IRenderable.h"

class MapManager;

class TileManager :public IRenderable, public ManagerBase
{
private:
	std::vector<Tile*> tiles;

public:

private:

public:
	TileManager();
	~TileManager();

	void AddTile(Tile* tile);
	Tile* GetTile(SpriteName spriteName);
	std::vector<Tile*> GetTiles(SpriteName spriteName);
	std::vector<Tile*> GetTilesList() { return tiles; }
	std::vector<Tile*> GetWalkableTiles();
	std::vector<Tile*> GetWalkableNeighboursOfTile(Tile* tile);
	Tile* GetTileAtPosition(Vector2D position);
	int GetTileIndexInList(Tile* tile);

	void Start() override;
	void Update() override;
	void Render() override;
	void Destroy() override;

	void DebugPositions();
	void CreateTilesFromMap(Managers* managers, int mapIndex);
	void ClearTiles();
};