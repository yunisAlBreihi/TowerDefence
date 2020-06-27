#include "TileManager.h"

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

void TileManager::DebugPositions()
{
	for (Tile* t: tiles)
	{
		std::cout << "X position: " << t->GetPosition().x << " Y position: " << t->GetPosition().y << std::endl;
	}
}