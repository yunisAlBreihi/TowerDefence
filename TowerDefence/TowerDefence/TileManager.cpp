#include "TileManager.h"

void TileManager::AddTile(Tile* tile)
{
	tiles.push_back(tile);
}

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

void TileManager::DebugPositions()
{
	for (Tile* t: tiles)
	{
		std::cout << "X position: " << t->GetPosition().x << " Y position: " << t->GetPosition().y << std::endl;
	}
}