#include "FrostBullet.h"
#include "FrostExplosion.h"
#include "Globals.h"

#pragma region Construction
FrostBullet::FrostBullet(BulletType bulletType, Sprite* sprite, Vector2D startPosition, Vector2D endPosition, Vector2D scale)
{
	managers = Managers::GetInstance();
	this->bulletType = bulletType;
	this->sprite = sprite;
	this->position = startPosition;
	this->startPosition = startPosition;
	this-> endPosition = endPosition;
	this->scale = scale;

	dstRect = { (int)this->position.x, (int)this->position.y, (int)this->scale.x, (int)this->scale.y };
	isActive = true;
}
#pragma endregion Construction

#pragma region Action
void FrostBullet::OnReachedDestination()
{
	EffectManager* effectsManager = managers->GetManager<EffectManager>(ManagerName::EffectsManager);
	FrostExplosion* frostExplosion = (FrostExplosion*)effectsManager->GetInactiveEffectOfType(bulletType);
	if (frostExplosion == nullptr)
	{
		frostExplosion = new FrostExplosion(bulletType, sprite, position, Vector2D::Zero(), Vector2D::One() * (Globals::DEFAULT_SPRITE_SIZE * 2.0f));
		effectsManager->AddEffect(frostExplosion);
	}
	else
	{
		frostExplosion->Reset(bulletType, sprite, position, Vector2D::Zero(), Vector2D::One() * (Globals::DEFAULT_SPRITE_SIZE * 2.0f));
	}
}
#pragma endregion Action