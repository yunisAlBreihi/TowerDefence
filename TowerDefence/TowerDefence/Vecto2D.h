#pragma once

struct Vector2D
{
	int x;
	int y;

	Vector2D(int x, int y) : x(x), y(y) {}

	bool operator==(const Vector2D other) 
	{
		if (other.x == x && other.y == y)
		{
			return true;
		}
		return false;
	}
};