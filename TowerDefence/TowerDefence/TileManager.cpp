#include "TileManager.h"
#include "Globals.h"
#include "MapManager.h"
#include "SpriteManager.h"

TileManager::TileManager()
{
	name = ManagerName::TileManager;
}

TileManager::~TileManager()
{
}

void TileManager::Start()
{
}

void TileManager::Update(float deltaTime)
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

void TileManager::ClearTiles()
{
	for (auto tile : tiles)
	{
		tile->Disable();
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

std::vector<Tile*> TileManager::GetTiles(SpriteName spriteName)
{
	std::vector<Tile*> tempTiles;

	for (Tile* tile : tiles)
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

	for (Tile* tile : tiles)
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
	for (Tile* tile : tiles)
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

void TileManager::DebugPositions()
{
	for (Tile* t : tiles)
	{
		std::cout << "X position: " << t->GetPosition().x << " Y position: " << t->GetPosition().y << std::endl;
	}
}

void TileManager::CreateTilesFromMap(Managers* managers, int mapIndex)
{
	MapManager* mapManager = managers->GetManager<MapManager>(ManagerName::MapManager);
	SpriteManager* spriteManager = managers->GetManager<SpriteManager>(ManagerName::SpriteManager);
	std::vector<std::vector<int>> tempTileNumbers = mapManager->GetMap(mapIndex)->GetTileNumbers();

	for (unsigned int col = 0; col < tempTileNumbers.size(); col++)
	{
		for (unsigned int row = 0; row < tempTileNumbers[col].size(); row++)
		{
			SpriteName tempSpriteName = (SpriteName)(tempTileNumbers[col][row]);

			//Set which tiles are walkable or not
			bool tempWalkable = false;
			if (tempSpriteName == SpriteName::StartPosition || tempSpriteName == SpriteName::EndPosition || tempSpriteName == SpriteName::Grass)
			{
				tempWalkable = true;
			}
			Tile* tempTile = GetInactiveTile();
			if (tempTile == nullptr)
			{
				tempTile = new Tile(managers, spriteManager->GetSprite(tempSpriteName),
					Vector2D(row * Globals::DEFAULT_SPRITE_SIZE, col * Globals::DEFAULT_SPRITE_SIZE),
					Vector2D(Globals::DEFAULT_SPRITE_SIZE, Globals::DEFAULT_SPRITE_SIZE), tempWalkable);
				AddTile(tempTile);
			}
			else
			{
				tempTile->Reset(managers, spriteManager->GetSprite(tempSpriteName),
					Vector2D(row * Globals::DEFAULT_SPRITE_SIZE, col * Globals::DEFAULT_SPRITE_SIZE),
					Vector2D(Globals::DEFAULT_SPRITE_SIZE, Globals::DEFAULT_SPRITE_SIZE), tempWalkable);
			}
		}
	}
}

Tile* TileManager::GetInactiveTile()
{
	for (auto tile : tiles)
	{
		if (tile->IsActive() == false)
		{
			return tile;
		}
	}
	std::cout << "Could not find an tile that is inactive, returning nullptr" << std::endl;
	return nullptr;
}
