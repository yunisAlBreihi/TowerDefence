#include "MapReader.h"
#include <fstream>

Map* MapReader::ReadMap(std::string filePath)
{
	std::ifstream fileStream;
	fileStream.open(filePath);
	std::vector<std::vector<char>> tempMapData;

	if (fileStream.is_open())
	{
		std::string line;

		//This runs while the file stream hasn't reached the end of the file
		while (fileStream)
		{
			getline(fileStream, line);
			std::vector<char> mapRow;

			for (int i = 0; i < line.size(); i++)
			{
				mapRow.push_back(line[i]);
			}
			tempMapData.push_back(mapRow);
			std::cout << line << std::endl;
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
