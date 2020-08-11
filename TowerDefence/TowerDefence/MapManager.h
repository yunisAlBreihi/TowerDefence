#pragma once
#include "SpriteManager.h"
#include "Tile.h"
#include "Map.h"
#include "Managers.h"

class MapManager : public ManagerBase
{
private:

	std::vector<Map*> maps;
	Managers* managers = nullptr;

public:

private:

public:

	MapManager( Managers* managers);
	void AddMap(Map* map);
	//void CreateTilesFromMap(int mapIndex);
	Map* GetMap(int index) { return maps[index]; }
};

