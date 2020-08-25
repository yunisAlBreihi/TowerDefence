#include "FrostExplosion.h"
#include "Globals.h"

#pragma region Construction
FrostExplosion::FrostExplosion(BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D startScale, Vector2D endScale)
{
	managers = Managers::GetInstance();
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
#pragma endregion Construction;

#pragma region Action
void FrostExplosion::OnHit(Enemy* enemy)
{
	enemy->TakeDamage((float)Globals::dRand(0.1, 0.3));
	enemy->Freeze((float)Globals::dRand(1.5f, 3.0f), (float)Globals::dRand(0.5, 0.95));
}
#pragma endregion Action
