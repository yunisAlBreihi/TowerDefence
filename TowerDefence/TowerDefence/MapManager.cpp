#include "MapManager.h"
#include "GameManager.h"

MapManager::MapManager(SDL_Renderer* renderer, SpriteManager* spriteManager, TileManager* tileManager) : renderer(renderer), spriteManager(spriteManager), tileManager(tileManager)
{
}

void MapManager::AddMap(Map* map)
{
	maps.push_back(map);
}

void MapManager::CreateMap(int mapIndex)
{
	std::vector<std::vector<char>> tempTileNumbers = maps[mapIndex]->GetTileNumbers();

	for (int col = 0; col < tempTileNumbers.size(); col++)
	{
		for (int row = 0; row < tempTileNumbers[col].size(); row++)
		{
			int spriteNameIndex = (int)(tempTileNumbers[col][row] - 48);
			SpriteName tempSpriteName = (SpriteName)(spriteNameIndex);
			Tile* tempTile = new Tile(renderer, spriteManager->GetSprite(tempSpriteName), Vector2D(row * GameManager::DEFAULT_SPRITE_SIZE, col * GameManager::DEFAULT_SPRITE_SIZE), Vector2D(GameManager::DEFAULT_SPRITE_SIZE, GameManager::DEFAULT_SPRITE_SIZE));
			tileManager->AddTile(tempTile);
		}
	}
}
