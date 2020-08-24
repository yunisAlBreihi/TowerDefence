#pragma once
#include <string>
#include "Map.h"

class MapReader
{
public:
	Map* ReadMap(std::string filePath);
};