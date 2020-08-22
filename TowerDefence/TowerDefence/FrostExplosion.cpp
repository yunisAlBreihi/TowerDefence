#include "FrostExplosion.h"

FrostExplosion::FrostExplosion(Managers* managers,BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D startScale, Vector2D endScale)
{
	this->managers = managers;
	this->bulletType = bulletType;
	this->sprite = sprite;
	this->position = position;
	this->scale = startScale;
	this->startScale = startScale;
	this->endScale = endScale;

	this->enemyManager = this->managers->GetManager<EnemyManager>(ManagerName::EnemyManager);
	this->startPosition = this->position;
	this->endPosition = this->startPosition - (this->endScale * 0.5f);
	this->dstRect = { (int)this->startPosition.x, (int)this->startPosition.y, (int)this->scale.x, (int)this->scale.y };
	this->startScale = this->scale;
	this->collider = new Collider(this->startPosition, this->startScale.x * 0.5f);
	this->isActive = true;
}

void FrostExplosion::OnHit(Enemy* enemy)
{
	enemy->TakeDamage(damage);
	enemy->Freeze(freezeTime, freezeSpeed);
}
