#pragma once
#include <vector>
#include "ManagerBase.h"
#include "Managers.h"
#include "Tile.h"
#include "IRenderable.h"
class TileManager :public IRenderable, public ManagerBase
{
private:
	std::vector<Tile*> tiles;

public:
	TileManager();

	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;

	Tile* GetInactiveTile();
	void DebugPositions();
	void CreateTilesFromMap(Managers* managers, int mapIndex);
	void ClearTiles();
	void AddTile(Tile* tile);

	Tile* GetTileWithSprite(SpriteName spriteName);
	std::vector<Tile*> GetTilesWithSprite(SpriteName spriteName);
	std::vector<Tile*> GetTilesList() { return tiles; }
	std::vector<Tile*> GetWalkableTiles();
	std::vector<Tile*> GetWalkableNeighboursOfTile(Tile* tile);
	Tile* GetTileAtPosition(Vector2D position);
	int GetTileIndexInList(Tile* tile);
};