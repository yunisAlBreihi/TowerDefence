#pragma once
#include <random>

namespace Globals
{
	static const int DEFAULT_SPRITE_SIZE = 48;
	static const int DEFAULT_SCREENSIZE_W = 1280;
	static const int DEFAULT_SCREENSIZE_H = 720;

	//For randomizing doubles
	static std::random_device rd;  
	static std::mt19937 gen(rd()); 
	static double dRand(double min, double max)
	{
		std::uniform_real_distribution<> dis(min, max);
		return dis(gen);
	}
}
