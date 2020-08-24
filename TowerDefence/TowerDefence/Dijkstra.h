#pragma once
#include <vector>
#include "Tile.h"

class Dijkstra
{
public:
	std::vector<Tile*> FindShortestPath(Tile* start, Tile* goal);
};