#include "FrostBullet.h"
#include "FrostExplosion.h"
#include "GameManager.h"

FrostBullet::FrostBullet(Managers* managers,BulletType bulletType, Sprite* sprite, Vector2D startPosition, Vector2D endPosition, Vector2D scale)
{
	this->managers = managers;
	this->bulletType = bulletType;
	this->sprite = sprite;
	this->position = startPosition;
	this->startPosition = startPosition;
	this-> endPosition = endPosition;
	this->scale = scale;

	dstRect = { this->position.x, this->position.y, this->scale.x, this->scale.y };
	isActive = true;
}

FrostBullet::~FrostBullet()
{
}

void FrostBullet::OnReachedDestination()
{
	EffectsManager* effectsManager = managers->GetManager<EffectsManager>(ManagerName::EffectsManager);
	FrostExplosion* frostExplosion = (FrostExplosion*)effectsManager->GetInactiveEffect();
	if (frostExplosion == nullptr)
	{
		frostExplosion = new FrostExplosion(managers, bulletType, sprite, position, Vector2D::Zero(), Vector2D::One() * (GameManager::DEFAULT_SPRITE_SIZE * 2.0f));
		effectsManager->AddEffect(frostExplosion);
	}
	else
	{
		frostExplosion->Reset(managers, bulletType, sprite, position, Vector2D::Zero(), Vector2D::One() * (GameManager::DEFAULT_SPRITE_SIZE * 2.0f));
	}
}