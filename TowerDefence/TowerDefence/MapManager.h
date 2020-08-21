#pragma once
#include "Tile.h"
#include "Map.h"

class MapManager : public ManagerBase
{
private:

	std::vector<Map*> maps;

public:

private:

public:

	MapManager();
	void AddMap(Map* map);
	Map* GetMap(int index) { return maps[index]; }
	std::vector<Map*> GetMaps() { return maps; }
};

