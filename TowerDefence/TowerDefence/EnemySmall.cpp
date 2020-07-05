#include "EnemySmall.h"

EnemySmall::EnemySmall(SDL_Renderer* renderer, std::vector<Tile*> path, Sprite* sprite, Vector2D position, Vector2D scale)
{
	this->renderer = renderer;
	this->path = path;
	this->sprite = sprite;
	this->position = position;
	this->scale = scale;

	dstRect = { this->position.x, this->position.y, this->scale.x, this->scale.y };
}