#include "EnemySmall.h"

EnemySmall::EnemySmall(Managers* managers, std::vector<Tile*> path,std::string name, Sprite* sprite, Vector2D position, Vector2D scale)
{
	this->maxHealth = 3.0f;
	this->managers = managers;
	this->path = path;
	this->name = name;
	this->sprite = sprite;
	this->position = position;
	this->scale = scale;
	this->health = this->maxHealth;


	dstRect = { this->position.x, this->position.y, this->scale.x, this->scale.y };
	this->isActive = true;
}