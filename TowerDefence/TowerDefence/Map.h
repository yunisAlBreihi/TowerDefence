#pragma once
#include <vector>

class Map
{
private:
	std::vector<std::vector<char>> mapData;

public:

private:
public:
	Map(std::vector<std::vector<char>> mapData);
	std::vector<std::vector<char>> GetMapData() { return mapData; }

	std::vector<std::vector<char>> GetTileNumbers();
};

