#include "Timer.h"
#include <SDL.h>

using namespace std::literals::chrono_literals;

Timer::Timer()
{
	frameStart = SDL_GetTicks();
}

Timer::~Timer()
{

}

void Timer::SetDeltaTime()
{
	deltaTime = SDL_GetTicks() - frameStart;
}

void Timer::LimitTo60FPS()
{
	if (frameDelay > deltaTime)
	{
		SDL_Delay(frameDelay - deltaTime);
	}
}

int Timer::DeltaTime()
{
	return deltaTime;
}
