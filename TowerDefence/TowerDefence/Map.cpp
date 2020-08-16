#include "Map.h"
#include <iostream>
#include <sstream>

Map::Map(std::vector<std::string> mapData) : mapData(mapData)
{
}

std::vector<std::vector<int>> Map::GetTileNumbers()
{
	std::vector<std::vector<int>> tempTileNumbers;

	for (std::string row : mapData)
	{
		if (row.at(0) == '#')
		{
			break;
		}
		std::vector<int> tempTileNumberRow;
		for (char number : row)
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

	for (std::string row : mapData)
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
	//Prints out the enemy numbers for the map
	//for (std::vector<int> row : tempEnemyNumbers)
	//{
	//	for(int number : row)
	//	{
	//		std::cout << number;
	//	}
	//	std::cout << std::endl;
	//}
	return tempEnemyNumbers;
}

void Map::DebugMapData()
{
	for (std::string row : mapData)
	{
		std::cout << row << std::endl;
	}
}
