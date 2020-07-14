#include "TowerBig.h"

TowerBig::TowerBig(SDL_Renderer* renderer, EnemyManager* enemyManager, SpriteManager* spriteManager,BulletManager* bulletManager, Sprite* sprite, Vector2D position, Vector2D scale)
{
	this->renderer = renderer;
	this->enemyManager = enemyManager;
	this->spriteManager = spriteManager;
	this->bulletManager = bulletManager;
	this->sprite = sprite;
	this->position = position;
	this->scale = scale;
	dstRect = { this->position.x, this->position.y, this->scale.x, this->scale.y };
}