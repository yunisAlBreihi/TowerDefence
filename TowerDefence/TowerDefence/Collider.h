#pragma once
#include <SDL.h>
#include "Vector2D.h"

class Collider
{
private:
	SDL_Renderer* renderer = nullptr;
	Vector2D position = {0.0f,0.0f};
	Vector2D debugCirclePosition = { 0.0f, 0.0f };
	float radius = 1.0f;

public:

private:

public:
	Collider(Vector2D position, float radius);

	bool isPointInCircle(Vector2D firstPosition, Vector2D secondPosition, float radius);
	void DrawDebugCircle(SDL_Renderer* renderer, Vector2D scale);

	Vector2D GetPosition() { return position; }
	void SetPosition(Vector2D position);
	void SetRadius(float radius);
};