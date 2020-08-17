#pragma once
#include <SDL.h>
#include "Vector2D.h"

class Collider
{
private:
	Vector2D position = {0.0f,0.0f};
	Vector2D debugCirclePosition = { 0.0f, 0.0f };
	float radius = 1.0f;

	//Sets the interval that the circle is drawn in steps. the higher number, the less it draws.
	int debugCircleQuality = 4;

public:

private:

public:
	Collider(Vector2D position, float radius);

	bool isPointInCircle(Vector2D targetPosition);
	void DrawDebugCircle(SDL_Renderer* renderer);

	void SetPosition(Vector2D position);
	Vector2D GetPosition() { return position; }
	void SetRadius(float radius);
	float GetRadius() { return radius; }
};