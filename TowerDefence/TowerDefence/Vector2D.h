#pragma once
#include <cmath>

struct Vector2D
{
	float x;
	float y;

	Vector2D(float x, float y) : x(x), y(y) {}

	static Vector2D Zero() { return Vector2D(0, 0); }
	static Vector2D One() { return Vector2D(1, 1); }

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
		float currentX = Lerp(startPosition.x, endPosition.x, delta);
		float currentY = Lerp(startPosition.y, endPosition.y, delta);
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
	
	const Vector2D operator+(const Vector2D other) 
	{
		return Vector2D(x + other.x, y + other.y);
	}

	const Vector2D operator-(const Vector2D other)
	{
		return Vector2D(x - other.x, y - other.y);
	}

	const Vector2D operator+(const int other)
	{
		return Vector2D(x + other, y + other);
	}

	const Vector2D operator*(const float other) 
	{
		return Vector2D(x * other, y * other);
	}

	const Vector2D operator/(const float other)
	{
		return Vector2D(x / other, y / other);
	}
};