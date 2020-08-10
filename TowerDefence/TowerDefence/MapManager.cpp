#include "MapManager.h"
#include "GameManager.h"

MapManager::MapManager(SDL_Renderer* renderer, Managers* managers) : renderer(renderer), managers(managers)
{
	name = ManagerName::MapManager;
}

void MapManager::AddMap(Map* map)
{
	maps.push_back(map);
}
