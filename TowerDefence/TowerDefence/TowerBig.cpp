#include "TowerBig.h"

TowerBig::TowerBig(Managers* managers,BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D scale)
{
	this->managers = managers;
	enemyManager = (EnemyManager*)managers->GetManager(ManagerName::EnemyManager);
	spriteManager = (SpriteManager*)managers->GetManager(ManagerName::SpriteManager);
	bulletManager = (BulletManager*)managers->GetManager(ManagerName::BulletManager);
	effectsManager = (EffectsManager*)managers->GetManager(ManagerName::EffectsManager);
	this->bulletType = bulletType;
	this->sprite = sprite;
	this->position = position;
	this->scale = scale;
	dstRect = { this->position.x, this->position.y, this->scale.x, this->scale.y };
}