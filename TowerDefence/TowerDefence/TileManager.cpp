#include "TileManager.h"
#include "Globals.h"
#include "MapManager.h"
#include "SpriteManager.h"

#pragma region Construction
TileManager::TileManager()
{
	name = ManagerName::TileManager;
}
#pragma endregion Construction

#pragma region GameLoop
void TileManager::Start()
{
}

void TileManager::Update(float deltaTime)
{
}

void TileManager::Render()
{
	for (const auto& tile : tiles)
	{
		tile->Render();
	}
}
#pragma endregion GameLoop

#pragma region GetTiles
Tile* TileManager::GetTileWithSprite(SpriteName spriteName)
{
	for (const auto& tile : tiles)
	{
		if (tile->GetSprite()->GetSpriteName() == spriteName)
		{
			return tile;
		}
	}
	std::cout << "Could not find the specified tile" << std::endl;
	return nullptr;
}

std::vector<Tile*> TileManager::GetTilesWithSprite(SpriteName spriteName)
{
	std::vector<Tile*> tempTiles;

	for (const auto& tile : tiles)
	{
		if (tile->GetSprite()->GetSpriteName() == spriteName)
		{
			tempTiles.push_back(tile);
		}
	}

	if (tempTiles.empty() == true)
	{
		std::cout << "Could not find any tiles with the sprite specified. Returning empty list" << std::endl;
		return std::vector<Tile*>();
	}

	return tempTiles;
}

std::vector<Tile*> TileManager::GetWalkableTiles()
{
	std::vector<Tile*> walkables;

	for (const auto& tile : tiles)
	{
		if (tile->IsWalkable() == true)
		{
			walkables.push_back(tile);
		}
	}

	if (walkables.empty() == true)
	{
		std::cout << "Could not find any walkable tiles with the sprite specified. Returning empty list" << std::endl;
		return std::vector<Tile*>();
	}

	return walkables;
}

std::vector<Tile*> TileManager::GetWalkableNeighboursOfTile(Tile* tile)
{
	std::vector<Tile*> neighbours;

	Tile* NTile = GetTileAtPosition(Vector2D(tile->GetPosition().x, tile->GetPosition().y + (1 * Globals::DEFAULT_SPRITE_SIZE)));
	Tile* STile = GetTileAtPosition(Vector2D(tile->GetPosition().x, tile->GetPosition().y - (1 * Globals::DEFAULT_SPRITE_SIZE)));
	Tile* WTile = GetTileAtPosition(Vector2D(tile->GetPosition().x - (1 * Globals::DEFAULT_SPRITE_SIZE), tile->GetPosition().y));
	Tile* ETile = GetTileAtPosition(Vector2D(tile->GetPosition().x + (1 * Globals::DEFAULT_SPRITE_SIZE), tile->GetPosition().y));

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
	for (const auto& tile : tiles)
	{
		if (tile->GetPosition() == position)
		{
			return tile;
		}
	}
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
	return -1;
}

Tile* TileManager::GetInactiveTile()
{
	for (const auto& tile : tiles)
	{
		if (tile->IsActive() == false)
		{
			return tile;
		}
	}
	std::cout << "Could not find an tile that is inactive, returning nullptr" << std::endl;
	return nullptr;
}
#pragma endregion GetTiles

#pragma region ManageTiles
void TileManager::CreateTilesFromMap(Managers* managers, int mapIndex)
{
	MapManager* mapManager = managers->GetManager<MapManager>(ManagerName::MapManager);
	SpriteManager* spriteManager = managers->GetManager<SpriteManager>(ManagerName::SpriteManager);
	std::vector<std::vector<int>> tempTileNumbers = mapManager->GetMapAtIndex(mapIndex)->GetTileNumbers();

	for (unsigned int col = 0; col < tempTileNumbers.size(); col++)
	{
		for (unsigned int row = 0; row < tempTileNumbers[col].size(); row++)
		{
			SpriteName tempSpriteName = (SpriteName)(tempTileNumbers[col][row]);

			//Set which tiles are walkable or not
			bool tempWalkable = false;
			if (tempSpriteName == SpriteName::EnemyBase || tempSpriteName == SpriteName::PlayerBase || tempSpriteName == SpriteName::Grass)
			{
				tempWalkable = true;
			}
			Tile* tempTile = GetInactiveTile();
			if (tempTile == nullptr)
			{
				tempTile = new Tile(managers, spriteManager->GetSprite(tempSpriteName),
					{ (float)(row * Globals::DEFAULT_SPRITE_SIZE), (float)(col * Globals::DEFAULT_SPRITE_SIZE) },
					{ (float)Globals::DEFAULT_SPRITE_SIZE, (float)Globals::DEFAULT_SPRITE_SIZE }, tempWalkable);
				AddTile(tempTile);
			}
			else
			{
				tempTile->Reset(managers, spriteManager->GetSprite(tempSpriteName),
					{ (float)(row * Globals::DEFAULT_SPRITE_SIZE), (float)(col * Globals::DEFAULT_SPRITE_SIZE) },
					{ (float)Globals::DEFAULT_SPRITE_SIZE, (float)Globals::DEFAULT_SPRITE_SIZE }, tempWalkable);
			}
		}
	}
}

void TileManager::ClearTiles()
{
	for (const auto& tile : tiles)
	{
		tile->Disable();
	}
}

void TileManager::AddTile(Tile* tile)
{
	tiles.push_back(tile);
}
#pragma endregion ManageTiles

#pragma region Debug
void TileManager::DebugPositions()
{
	for (const auto& t : tiles)
	{
		std::cout << "X position: " << t->GetPosition().x << " Y position: " << t->GetPosition().y << std::endl;
	}
}
#pragma endregion Debug