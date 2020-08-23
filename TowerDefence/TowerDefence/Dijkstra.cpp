#include <list>
#include <queue>
#include <unordered_map>
#include "Dijkstra.h"
#include "Managers.h"
#include "TileManager.h"

#pragma region Construction
Dijkstra::Dijkstra()
{
}

Dijkstra::~Dijkstra()
{
}
#pragma endregion Construction

#pragma region FindPath
std::vector<Tile*> Dijkstra::FindShortestPath(Tile* start, Tile* goal)
{
	Managers* managers = Managers::GetInstance();
	TileManager* tileManager = managers->GetManager<TileManager>(ManagerName::TileManager);

	std::queue<Tile*> frontier;
	frontier.push(start);

	std::unordered_map<Tile*, Tile*> came_from;
	came_from[start] = start;
	
	std::vector<Tile*> walkables = tileManager->GetWalkableTiles();

	while (frontier.empty() == false)
	{
		Tile* current = frontier.front();
		frontier.pop();

		if (current == goal)
		{
			break;
		}

		std::vector<Tile*> neighbours = tileManager->GetWalkableNeighboursOfTile(current);
		if (neighbours.empty() == false)
		{
			for (auto next : neighbours)
			{
				if (came_from.find(next) == came_from.end())
				{
					frontier.push(next);
					came_from[next] = current;
				}
			}
		}
	}

	//Reconstruct path to a single list of tiles/positions.
	std::vector<Tile*> path;
	Tile* current = goal;
	while (current != start)
	{
		path.push_back(current);
		current = came_from[current];
	}
	path.push_back(start);
	std::reverse(path.begin(), path.end());
	return path;
}
#pragma endregion FindPath