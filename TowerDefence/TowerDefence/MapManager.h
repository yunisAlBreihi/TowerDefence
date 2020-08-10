#pragma once
#include "SpriteManager.h"
#include "Tile.h"
#include "Map.h"
#include "Managers.h"

class MapManager : public ManagerBase
{
private:

	std::vector<Map*> maps;
	SDL_Renderer* renderer = nullptr;
	Managers* managers = nullptr;

public:

private:

public:

	MapManager(SDL_Renderer* renderer, Managers* managers);
	void AddMap(Map* map);
	//void CreateTilesFromMap(int mapIndex);
	SDL_Renderer* GetRenderer() { return renderer; }
	SpriteManager* GetSpriteManager() { return (SpriteManager*)managers->GetManager(ManagerName::SpriteManager); }
	Map* GetMap(int index) { return maps[index]; }
};

