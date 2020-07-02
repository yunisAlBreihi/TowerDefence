#include "TileManager.h"
#include "GameManager.h"
#include "MapManager.h"

void TileManager::Start()
{
}

void TileManager::Update()
{
}

void TileManager::Render()
{
	for (Tile* t : tiles)
	{
		t->Render();
	}
}

void TileManager::Destroy()
{
	for (Tile* t : tiles)
	{
		t->Destroy();
	}
}

void TileManager::AddTile(Tile* tile)
{
	tiles.push_back(tile);
}

Tile* TileManager::GetTile(SpriteName spriteName)
{
	for (Tile* t : tiles)
	{
		if (t->GetSprite()->GetSpriteName() == spriteName)
		{
			return t;
		}
	}
	std::cout << "Could not find the specified tile" << std::endl;
	return nullptr;
}

std::vector<Tile*> TileManager::GetWalkableTiles()
{
	std::vector<Tile*> walkables;

	for (Tile* tile : tiles)
	{
		if (tile->IsWalkable() == true)
		{
			walkables.push_back(tile);
		}
	}
	return walkables;
}

std::vector<Tile*> TileManager::GetWalkableNeighboursOfTile(Tile* tile)
{
	std::vector<Tile*> neighbours;

	Tile* NTile = GetTileAtPosition(Vector2D(tile->GetPosition().x, tile->GetPosition().y + (1 * GameManager::DEFAULT_SPRITE_SIZE)));
	Tile* STile = GetTileAtPosition(Vector2D(tile->GetPosition().x, tile->GetPosition().y - (1 * GameManager::DEFAULT_SPRITE_SIZE)));
	Tile* WTile = GetTileAtPosition(Vector2D(tile->GetPosition().x - (1 * GameManager::DEFAULT_SPRITE_SIZE), tile->GetPosition().y));
	Tile* ETile = GetTileAtPosition(Vector2D(tile->GetPosition().x + (1 * GameManager::DEFAULT_SPRITE_SIZE), tile->GetPosition().y));

	if (NTile != nullptr && NTile->IsWalkable() == true)
		neighbours.push_back(NTile);
	if (STile != nullptr && STile->IsWalkable() == true)
		neighbours.push_back(STile);
	if (WTile != nullptr && WTile->IsWalkable() == true)
		neighbours.push_back(WTile);
	if (ETile != nullptr && ETile->IsWalkable() == true)
		neighbours.push_back(ETile);

	if (NTile == nullptr && STile == nullptr && WTile == nullptr && ETile == nullptr)
	{
		std::cout << "Tile does not have any walkable neighbours. Returning empty list" << std::endl;
		return std::vector<Tile*>();
	}
	return neighbours;
}

Tile* TileManager::GetTileAtPosition(Vector2D position)
{
	for (Tile* tile : tiles)
	{
		if (tile->GetPosition() == position)
		{
			return tile;
		}
	}
	std::cout << "Could not find a Tile at position: " << std::endl << "x: " << position.x << " y: " << position.y << std::endl;
	return nullptr;
}

int TileManager::GetTileIndexInList(Tile* tile)
{
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		if (tile == tiles[i])
		{
			return i;
		}
	}
	std::cout << "Could not find the tile in the tile list. Returning -1" << std::endl;
	return -1;
}

void TileManager::DebugPositions()
{
	for (Tile* t : tiles)
	{
		std::cout << "X position: " << t->GetPosition().x << " Y position: " << t->GetPosition().y << std::endl;
	}
}

void TileManager::CreateTilesFromMap(MapManager* mapManager, int mapIndex)
{
	std::vector<std::vector<char>> tempTileNumbers = mapManager->GetMap(mapIndex)->GetTileNumbers();

	for (unsigned int col = 0; col < tempTileNumbers.size(); col++)
	{
		for (unsigned int row = 0; row < tempTileNumbers[col].size(); row++)
		{
			int spriteNameIndex = (int)(tempTileNumbers[col][row] - 48);
			SpriteName tempSpriteName = (SpriteName)(spriteNameIndex);

			//Set which tiles are walkable or not
			bool tempWalkable = false;
			if (tempSpriteName == SpriteName::startPosition || tempSpriteName == SpriteName::endPosition || tempSpriteName == SpriteName::grass)
			{
				tempWalkable = true;
			}
			Tile* tempTile = new Tile(mapManager->GetRenderer(), mapManager->GetSpriteManager()->GetSprite(tempSpriteName), Vector2D(row * GameManager::DEFAULT_SPRITE_SIZE, col * GameManager::DEFAULT_SPRITE_SIZE), Vector2D(GameManager::DEFAULT_SPRITE_SIZE, GameManager::DEFAULT_SPRITE_SIZE), tempWalkable);

			AddTile(tempTile);
		}
	}
}