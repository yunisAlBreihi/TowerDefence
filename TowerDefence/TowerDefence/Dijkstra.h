#pragma once
#include <unordered_map>

class TileManager;
class Tile;
class vector;

class Dijkstra
{
private:

public:

private:

public:
	std::vector<Tile*> FindShortestPath(TileManager* tileManager, Tile* start, Tile* goal);
};