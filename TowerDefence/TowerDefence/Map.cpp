#include "Map.h"

Map::Map(std::vector<std::vector<char>> mapData) : mapData(mapData)
{
}

std::vector<std::vector<char>> Map::GetTileNumbers()
{
	std::vector<std::vector<char>> tempTileNumbers;
	int rowIndex = 0;

	for (std::vector<char> row : mapData)
	{
		if (row.at(0) == '#')
		{
			break;
		}
		std::vector<char> tempTileNumberRow;
		for (char number : row)
		{
			tempTileNumberRow.push_back(number);
		}
		tempTileNumbers.push_back(tempTileNumberRow);
	}
	//Reverse the tile positions before returning them, so the map starts at bottom left and not top left
	std::vector<std::vector<char>> reversedTempTileNumbers;
	for (int i = tempTileNumbers.size() - 1; i >= 0; i--)
	{
		reversedTempTileNumbers.push_back(tempTileNumbers[i]);
	}
	return reversedTempTileNumbers;
}
