#pragma once
#include <vector>
#include <string>

class Map
{
private:
	std::vector<std::string> mapData;

public:
	Map(std::vector<std::string> mapData);

	std::vector<std::string> GetMapData() { return mapData; }
	std::vector<std::vector<int>> GetTileNumbers();
	std::vector<std::vector<int>> GetEnemyNumbers();
	void DebugMapData();
};