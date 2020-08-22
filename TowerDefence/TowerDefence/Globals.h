#pragma once
#include <random>

namespace Globals
{
	static const int DEFAULT_SPRITE_SIZE = 48;
	static const int DEFAULT_SCREENSIZE_W = 1280;
	static const int DEFAULT_SCREENSIZE_H = 720;

	static std::random_device rd;  //Will be used to obtain a seed for the random number engine
	static std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

	static double dRand(double min, double max)
	{
		std::uniform_real_distribution<> dis(min, max);
		return dis(gen);
	}
}
