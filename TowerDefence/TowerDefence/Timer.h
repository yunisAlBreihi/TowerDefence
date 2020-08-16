#pragma once
#include <cstdio>
#include <cstdint>

class Timer
{
private:
	const int fps = 60;
	const float target_deltaTime = 1.6f;

	float deltaTime = 0;
	uint64_t newTime = 0;
	uint64_t oldTime = 0;

public:
private:
public:
	Timer();
	~Timer();

	void Tick();

	float DeltaTime();
	int FPS();
	void LogDeltaTime();
};