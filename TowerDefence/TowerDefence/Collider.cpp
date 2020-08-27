#include "Collider.h"
#include <cmath>

#pragma region Construction
Collider::Collider(Vector2D position, float radius) : position(position), radius(radius)
{
}
#pragma endregion Construction

#pragma region CollisionChecks
bool Collider::isPointInCircle(Vector2D targetPosition)
{
	return ((position.x - targetPosition.x) * (position.x - targetPosition.x) + (position.y - targetPosition.y) * (position.y - targetPosition.y)) < (radius * radius);
}
#pragma endregion CollisionChecks

#pragma region Set
void Collider::SetPosition(Vector2D position)
{
	//Round the values, since SDL_Rect positions is in int, otherwise get Stutter
	this->position = Vector2D(round(position.x),round(position.y));
}

void Collider::SetRadius(float radius)
{
	this->radius = radius;
}
#pragma endregion Set

#pragma region Debug
void Collider::DrawDebugCircle(SDL_Renderer* renderer)
{
	if (radius > 0)
	{
		for (unsigned int i = 0; i < 360; i += debugCircleQuality)
		{
			debugCirclePosition = Vector2D((float)(position.x + radius * std::cos(i)), (float)(position.y + radius * std::sin(i)));
			SDL_SetRenderDrawColor(renderer, 230, 0, 126, 255);
			SDL_RenderDrawPoint(renderer, (int)round(debugCirclePosition.x + radius), (int)round(debugCirclePosition.y + radius));
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		}
	}
}
#pragma endregion Debug