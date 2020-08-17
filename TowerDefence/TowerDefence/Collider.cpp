#include "Collider.h"
#include <cmath>

Collider::Collider(Vector2D position, float radius) : position(position), radius(radius)
{
}

bool Collider::isPointInCircle(Vector2D targetPosition)
{
	return ((position.x - targetPosition.x) * (position.x - targetPosition.x) + (position.y - targetPosition.y) * (position.y - targetPosition.y)) < radius * radius;
}

void Collider::DrawDebugCircle(SDL_Renderer* renderer)
{
	if (radius > 0)
	{
		for (size_t i = 0; i < 360; i += debugCircleQuality)
		{
			debugCirclePosition = Vector2D(position.x + radius * std::cos(i), position.y + radius * std::sin(i));
			SDL_SetRenderDrawColor(renderer, 230, 0, 126, 255);
			SDL_RenderDrawPoint(renderer, debugCirclePosition.x + radius, debugCirclePosition.y + radius);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		}
	}
}

void Collider::SetPosition(Vector2D position)
{
	this->position = position;
}

void Collider::SetRadius(float radius)
{
	this->radius = radius;
}