#pragma once
#include "Tile.h"
#include "Map.h"

class MapManager : public ManagerBase
{
private:
	std::vector<Map*> maps;

public:
	MapManager();
	~MapManager();

	void AddMap(Map* map);
	Map* GetMapAtIndex(int index) { return maps[index]; }
	std::vector<Map*> GetMaps() { return maps; }
};