#include "EnemyManager.h"
#include "TileManager.h"

EnemyManager::EnemyManager(SDL_Renderer* renderer, TileManager* tileManager, Dijkstra* dijkstra) : renderer(renderer), tileManager(tileManager), dijkstra(dijkstra)
{
}

void EnemyManager::Start()
{
	path = dijkstra->FindShortestPath(tileManager, tileManager->GetTile(SpriteName::startPosition), tileManager->GetTile(SpriteName::endPosition));

	//for (EnemyBase* e : enemies)
	//{
	//	e->Start();
	//}
}

void EnemyManager::Update()
{
	//TODO: replace this delay with a deltaTime instead
	SDL_Delay(500);

	for (EnemyBase* e : enemies)
	{
		e->SetPosition(path[pathIndex]->GetPosition());
	}

	if (pathIndex < path.size()-1)
	{
		pathIndex += 1;
	}
}

void EnemyManager::Render()
{
	for (EnemyBase* e : enemies)
	{
		SDL_RenderCopy(renderer, e->GetSprite()->GetTexture(), nullptr, &(e->GetDstRect()));
		e->Render();
	}
}

void EnemyManager::Destroy()
{
	for (EnemyBase* e : enemies)
	{
		e->Destroy();
	}
}

void EnemyManager::DebugPositions()
{
	for (EnemyBase* e : enemies)
	{
		std::cout << "X position: " << e->GetPosition().x << " Y position: " << e->GetPosition().y << std::endl;
	}
}

void EnemyManager::AddEnemy(EnemyBase* enemy)
{
	enemies.push_back(enemy);
}
