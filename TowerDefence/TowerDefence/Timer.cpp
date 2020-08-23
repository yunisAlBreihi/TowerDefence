#include "Timer.h"
#include <SDL.h>
#include <iostream>

#pragma region Construction
Timer::Timer()
{
}

Timer::~Timer()
{
}
#pragma endregion Construction

#pragma region ManageTime
void Timer::Tick()
{
	newTime = SDL_GetPerformanceCounter();

	//Ends with scaling down by 1000.0f to reformat to seconds
	deltaTime = (float)((newTime - oldTime) * 1000 / (float)SDL_GetPerformanceFrequency()) / 1000.0f;

	//Scale down the deltaTime in case it is too high
	if (deltaTime > target_deltaTime)
	{
		deltaTime = target_deltaTime;
	}
	oldTime = newTime;
}
#pragma endregion ManageTime

#pragma region Debug
void Timer::LogDeltaTime()
{
	SDL_Log("%f", deltaTime);
}
#pragma endregion Debug