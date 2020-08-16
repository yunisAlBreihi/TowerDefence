#pragma once
#include <chrono>
#include <thread>

class Timer
{
private:
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	int frameStart = 0;
	float deltaTime = 0;

public:
private:
public:
	Timer();
	~Timer();

	void SetDeltaTime();
	void LimitTo60FPS();

	int DeltaTime();
};