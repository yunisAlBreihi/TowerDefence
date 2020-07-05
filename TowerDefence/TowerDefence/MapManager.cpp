#include "MapManager.h"
#include "GameManager.h"

MapManager::MapManager(SDL_Renderer* renderer, SpriteManager* spriteManager) : renderer(renderer), spriteManager(spriteManager)
{
}

void MapManager::AddMap(Map* map)
{
	maps.push_back(map);
}
