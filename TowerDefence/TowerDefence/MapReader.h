#pragma once
#include <string>
#include "Map.h"

class MapReader
{
public:
	MapReader();
	~MapReader();

	Map* ReadMap(std::string filePath);
};

