#include "Tile.h"

Tile::Tile(SDL_Renderer* renderer, Sprite* sprite, Vector2D position, Vector2D scale, bool isWalkable) : renderer(renderer), sprite(sprite), position(position), scale(scale), isWalkable(isWalkable)
{
	dstRect = { this->position.x,this->position.y,this->scale.x, this->scale.y };
}

void Tile::Start()
{
}

void Tile::Update()
{
}

void Tile::Render()
{
	SDL_RenderCopy(renderer, sprite->GetTexture(), nullptr, &dstRect);
}

void Tile::Destroy()
{
	renderer = nullptr;
}

void Tile::SetPosition(Vector2D vector2D)
{
	position = vector2D;
	dstRect.x = position.x;
	dstRect.y = position.y;
}

Vector2D Tile::GetPosition()
{
	return Vector2D(dstRect.x, dstRect.y);
}

Sprite* Tile::GetSprite()
{
	return sprite;
}
