#pragma once
#include <math.h>

struct Vector2D
{
	int x;
	int y;

	Vector2D(int x, int y) : x(x), y(y) {}

	Vector2D Zero() { return Vector2D(0, 0); }

	static float Distance(Vector2D startPosition, Vector2D endPosition)
	{
		float pwrV = std::pow(endPosition.x - startPosition.x, 2);
		float pwrW = std::pow(endPosition.y - startPosition.y, 2);

		float distance = std::sqrt(pwrV + pwrW);
		return distance;
	}

	static float Lerp(float start, float end, float delta)
	{
		return (start * (1 - delta)) + (end * delta);
	}

	static Vector2D Lerp(Vector2D startPosition, Vector2D endPosition, float delta)
	{
		float tempDelta = delta;

		if (tempDelta >= 1)
		{
			tempDelta = 1.0f;
		}

		float currentX = Lerp(startPosition.x, endPosition.x, tempDelta);
		float currentY = Lerp(startPosition.y, endPosition.y, tempDelta);
		return Vector2D(currentX, currentY);
	}

	bool operator==(const Vector2D other)
	{
		if (other.x == x && other.y == y)
		{
			return true;
		}
		return false;
	}
};