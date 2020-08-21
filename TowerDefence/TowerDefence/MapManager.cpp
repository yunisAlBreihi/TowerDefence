#include "MapManager.h"
#include "GameManager.h"

MapManager::MapManager()
{
	name = ManagerName::MapManager;
}

void MapManager::AddMap(Map* map)
{
	maps.push_back(map);
}
