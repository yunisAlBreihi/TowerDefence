#include "FrostBullet.h"
#include "FrostExplosion.h"
#include "Globals.h"

FrostBullet::FrostBullet(Managers* managers,BulletType bulletType, Sprite* sprite, Vector2D startPosition, Vector2D endPosition, Vector2D scale)
{
	this->managers = managers;
	this->bulletType = bulletType;
	this->sprite = sprite;
	this->position = startPosition;
	this->startPosition = startPosition;
	this-> endPosition = endPosition;
	this->scale = scale;

	dstRect = { (int)this->position.x, (int)this->position.y, (int)this->scale.x, (int)this->scale.y };
	isActive = true;
}

FrostBullet::~FrostBullet()
{
}

void FrostBullet::OnReachedDestination()
{
	EffectsManager* effectsManager = managers->GetManager<EffectsManager>(ManagerName::EffectsManager);
	FrostExplosion* frostExplosion = (FrostExplosion*)effectsManager->GetInactiveEffectOfType(bulletType);
	if (frostExplosion == nullptr)
	{
		frostExplosion = new FrostExplosion(managers, bulletType, sprite, position, Vector2D::Zero(), Vector2D::One() * (Globals::DEFAULT_SPRITE_SIZE * 2.0f));
		effectsManager->AddEffect(frostExplosion);
	}
	else
	{
		frostExplosion->Reset(managers, bulletType, sprite, position, Vector2D::Zero(), Vector2D::One() * (Globals::DEFAULT_SPRITE_SIZE * 2.0f));
	}
}