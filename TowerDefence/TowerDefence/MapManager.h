#pragma once
#include "SpriteManager.h"
#include "TileManager.h"
#include "Tile.h"
#include "Map.h"

class MapManager
{
private:

	std::vector<Map*> maps;
	SDL_Renderer* renderer = nullptr;
	SpriteManager* spriteManager = nullptr;

public:

private:

public:

	MapManager(SDL_Renderer* renderer, SpriteManager* spriteManager);
	void AddMap(Map* map);
	//void CreateTilesFromMap(int mapIndex);
	SDL_Renderer* GetRenderer() { return renderer; }
	SpriteManager* GetSpriteManager() { return spriteManager; }
	Map* GetMap(int index) { return maps[index]; }

};

