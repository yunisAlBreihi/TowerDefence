#include "Map.h"
#include <iostream>
#include <sstream>

#pragma region Construction
Map::Map(std::vector<std::string> mapData) : mapData(mapData)
{
}
#pragma  endregion Construction

#pragma region GetData
std::vector<std::vector<int>> Map::GetTileNumbers()
{
	std::vector<std::vector<int>> tempTileNumbers;

	for (const auto& row : mapData)
	{
		if (row.at(0) == '#')
		{
			break;
		}
		std::vector<int> tempTileNumberRow;
		for (const auto& number : row)
		{
			tempTileNumberRow.push_back((int)(number - 48));
		}
		tempTileNumbers.push_back(tempTileNumberRow);
	}
	//Reverse the tile positions before returning them, so the map starts at bottom left and not top left
	std::vector<std::vector<int>> reversedTempTileNumbers;
	for (int i = tempTileNumbers.size() - 1; i >= 0; i--)
	{
		reversedTempTileNumbers.push_back(tempTileNumbers[i]);
	}
	return reversedTempTileNumbers;
}

std::vector<std::vector<int>> Map::GetEnemyNumbers()
{
	std::vector<std::vector<int>> tempEnemyNumbers;
	int rowIndex = 0;
	bool isOnEnemyNumbers = false;
	int enemyNumber = INT_MAX;

	for (const auto& row : mapData)
	{
		std::stringstream input(row);
		if (isOnEnemyNumbers == true)
		{
			std::vector<int> tempEnemyNumberRow;

			while (input.eof() == false)
			{
				input >> enemyNumber;
				tempEnemyNumberRow.push_back(enemyNumber);
			}
			tempEnemyNumbers.push_back(tempEnemyNumberRow);
		}
		if (row.at(0) == '#')
		{
			isOnEnemyNumbers = true;
		}
	}
	return tempEnemyNumbers;
}
#pragma endregion GetData

#pragma region Debug
void Map::DebugMapData()
{
	for (const auto& row : mapData)
	{
		std::cout << row << std::endl;
	}
}
#pragma endregion Debug
