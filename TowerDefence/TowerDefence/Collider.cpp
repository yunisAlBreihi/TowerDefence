#include "Collider.h"
#include <cmath>

Collider::Collider(Vector2D position, float radius) : position(position), radius(radius)
{
}

bool Collider::isPointInCircle(Vector2D firstPosition, Vector2D secondPosition, float radius)
{
	return ((firstPosition.x - secondPosition.x) * (firstPosition.x - secondPosition.x) + (firstPosition.y - secondPosition.y) * (firstPosition.y - secondPosition.y)) < radius * radius;
}

void Collider::DrawDebugCircle(SDL_Renderer* renderer ,Vector2D scale)
{
	if (radius > 0)
	{
		for (size_t i = 0; i < 360; i += 4)
		{
			debugCirclePosition = Vector2D(GetPosition().x + radius * std::cos(i), GetPosition().y + radius * std::sin(i));
			SDL_SetRenderDrawColor(renderer, 230, 0, 126, 255);
			SDL_RenderDrawPoint(renderer, debugCirclePosition.x + scale.x / 2, debugCirclePosition.y + scale.y / 2);
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