#include "TowerBig.h"

TowerBig::TowerBig(SDL_Renderer* renderer, Sprite* sprite, Vector2D position, Vector2D scale)
{
	this->renderer = renderer;
	this->sprite = sprite;
	this->position = position;
	this->scale = scale;
	dstRect = { this->position.x, this->position.y, this->scale.x, this->scale.y };
}