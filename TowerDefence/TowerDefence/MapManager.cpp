#include "MapManager.h"

#pragma region Construction
MapManager::MapManager()
{
	name = ManagerName::MapManager;
}

MapManager::~MapManager()
{
}
#pragma endregion Construction

#pragma region ManageMaps
void MapManager::AddMap(Map* map)
{
	maps.push_back(map);
}
#pragma endregion ManageMaps