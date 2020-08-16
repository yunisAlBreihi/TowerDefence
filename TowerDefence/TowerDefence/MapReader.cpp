#include "MapReader.h"
#include <iostream>
#include <fstream>

Map* MapReader::ReadMap(std::string filePath)
{
	std::ifstream fileStream;
	fileStream.open(filePath);
	std::vector<std::string> tempMapData;

	if (fileStream.is_open())
	{
		std::string line;

		//This runs while the file stream hasn't reached the end of the file
		while (fileStream)
		{
			getline(fileStream, line);
			std::string mapRow;

			for (unsigned int i = 0; i < line.size(); i++)
			{
				mapRow.push_back(line[i]);
			}
			tempMapData.push_back(mapRow);
			fileStream >> std::ws;
		}
		fileStream.close();
		return new Map(tempMapData);
	}
	else
	{
		std::cout << "Cannot open file: " << filePath << std::endl;
		return nullptr;
	}
	return nullptr;
}
