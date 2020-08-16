#include "Timer.h"
#include <SDL.h>
#include <iostream>

Timer::Timer()
{

}

Timer::~Timer()
{

}

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

float Timer::DeltaTime()
{
	return deltaTime;
}

int Timer::FPS()
{
	return fps;
}

void Timer::LogDeltaTime()
{
	SDL_Log("%f", deltaTime);
}
