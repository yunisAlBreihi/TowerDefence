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
	TileManager* tileManager = nullptr;

public:

private:

public:

	MapManager(SDL_Renderer* renderer, SpriteManager* spriteManager, TileManager* tileManager);
	void AddMap(Map* map);
	void CreateMap(int mapIndex);
	SDL_Renderer* GetRenderer() { return renderer; }
	SpriteManager* GetSpriteManager() { return spriteManager; }
};

