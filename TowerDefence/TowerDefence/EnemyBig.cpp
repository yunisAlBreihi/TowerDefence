#include "EnemyBig.h"

EnemyBig::EnemyBig(Managers* managers, std::vector<Tile*> path, Sprite* sprite, Vector2D position, Vector2D scale)
{
	health = 5.0f;
	this->managers = managers;
	this->path = path;
	this->sprite = sprite;
	this->position = position;
	this->scale = scale;

	dstRect = { this->position.x, this->position.y, this->scale.x, this->scale.y };
}