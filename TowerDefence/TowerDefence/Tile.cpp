#include "Tile.h"

Tile::Tile(Managers* managers, Sprite* sprite, Vector2D position, Vector2D scale, bool isWalkable) : managers(managers), sprite(sprite), position(position), scale(scale), isWalkable(isWalkable)
{
	dstRect = { this->position.x,this->position.y,this->scale.x, this->scale.y };
	isActive = true;
}

void Tile::Start()
{
}

void Tile::Update(float deltaTime)
{
}

void Tile::Render()
{
	if (isActive == true)
	{
		SDL_RenderCopy(managers->GetRenderer(), sprite->GetTexture(), nullptr, &dstRect);
	}
}

void Tile::Destroy()
{
	managers = nullptr;
}

void Tile::Disable()
{
	isActive = false;
}

void Tile::Reset(Managers* managers, Sprite* sprite, Vector2D position, Vector2D scale, bool isWalkable)
{
	this->managers = managers;
	this->sprite = sprite;
	this->position = position;
	this->scale = scale;
	this->isWalkable = isWalkable;

	this->dstRect = { this->position.x,this->position.y,this->scale.x, this->scale.y };
	this->isActive = true;
}

void Tile::SetPosition(Vector2D position)
{
	this->position = position;
	dstRect.x = this->position.x;
	dstRect.y = this->position.y;
}

void Tile::SetScale(Vector2D scale)
{
	this->scale = scale;
	dstRect.w = this->scale.x;
	dstRect.h = this->scale.y;
}
