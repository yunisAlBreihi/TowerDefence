#include "TileManager.h"

void TileManager::AddTile(Tile* tile)
{
	tileList.push_back(tile);
}

void TileManager::Start()
{
}

void TileManager::Update()
{
}

void TileManager::Render()
{
	for (Tile* t : tileList)
	{
		t->Render();
	}
}

void TileManager::Destroy()
{
	for (Tile* t : tileList)
	{
		t->Destroy();
	}
}

void TileManager::DebugPositions()
{
	for (Tile* t: tileList)
	{
		std::cout << "X position: " << t->GetPosition().x << " Y position: " << t->GetPosition().y << std::endl;
	}
}