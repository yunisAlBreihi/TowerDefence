#include "FrostExplosion.h"

FrostExplosion::FrostExplosion(Managers* managers, Sprite* sprite, Vector2D position, Vector2D startScale, Vector2D endScale)
{
	this->managers = managers;
	this->sprite = sprite;
	this->position = position;
	this->scale = startScale;
	this->startScale = startScale;
	this->endScale = endScale;

	this->enemyManager = this->managers->GetManager<EnemyManager>(ManagerName::EnemyManager);
	this->startPosition = this->position;
	this->endPosition = this->startPosition - (this->endScale * 0.5f);
	this->dstRect = { this->startPosition.x, this->startPosition.y, this->scale.x, this->scale.y };
	this->startScale = this->scale;
	this->collider = new Collider(this->startPosition, this->startScale.x * 0.5f);
}

void FrostExplosion::OnHit(EnemyBase* enemy)
{
	enemy->TakeDamage(damage);
	enemy->Freeze(freezeTime, freezeSpeed);
}
