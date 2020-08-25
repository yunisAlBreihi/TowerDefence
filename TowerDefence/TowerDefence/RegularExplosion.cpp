#include "RegularExplosion.h"
#include "Globals.h"

#pragma region Construction
RegularExplosion::RegularExplosion(BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D startScale, Vector2D endScale)
{
	managers = managers->GetInstance();
	this->bulletType = bulletType;
	this->sprite = sprite;
	this->position = position;
	this->startScale = startScale;
	this->endScale = endScale;

	this->enemyManager = this->managers->GetManager<EnemyManager>(ManagerName::EnemyManager);
	this->startPosition = this->position;
	this->endPosition = this->startPosition - (this->endScale * 0.5f);
	this->scale = this->startScale;
	this->dstRect = { (int)this->startPosition.x, (int)this->startPosition.y, (int)this->scale.x, (int)this->scale.y };
	this->startScale = this->scale;
	this->collider = new Collider(this->startPosition, this->startScale.x * 0.5f);
	this->isActive = true;
}
#pragma endregion Construction

#pragma region Action
void RegularExplosion::OnHit(Enemy* enemy)
{
	enemy->TakeDamage((float)Globals::dRand(0.1, 0.5));
}
#pragma endregion Action
