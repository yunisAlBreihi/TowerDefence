#include "RegularBullet.h"
#include "RegularExplosion.h"
#include "Globals.h"

#pragma region Construction
RegularBullet::RegularBullet( BulletType bulletType, Sprite* sprite, Vector2D startPosition, Vector2D endPosition, Vector2D scale)
{
	managers = Managers::GetInstance();
	spriteManager = managers->GetManager<SpriteManager>(ManagerName::SpriteManager);

	this->bulletType = bulletType;
	this->sprite = sprite;
	this->position = startPosition;
	this->startPosition = startPosition;
	this->endPosition = endPosition;
	this->scale = scale;

	dstRect = { (int)this->position.x, (int)this->position.y, (int)this->scale.x, (int)this->scale.y };
	isActive = true;
}
#pragma endregion Construction

#pragma region Action
void RegularBullet::OnReachedDestination()
{
	EffectManager* effectsManager = managers->GetManager<EffectManager>(ManagerName::EffectsManager);
	RegularExplosion* explosion = (RegularExplosion*)effectsManager->GetInactiveEffectOfType(bulletType);
	if (explosion == nullptr)
	{
		explosion = new RegularExplosion(bulletType, spriteManager->GetSprite(SpriteName::RegularExplosion), position, Vector2D::Zero(), Vector2D::One() * (Globals::DEFAULT_SPRITE_SIZE * 2.0f));
		effectsManager->AddEffect(explosion);
	}
	else
	{
		explosion->Reset(bulletType, spriteManager->GetSprite(SpriteName::RegularExplosion), position, Vector2D::Zero(), Vector2D::One() * (Globals::DEFAULT_SPRITE_SIZE * 2.0f));
	}
}
#pragma endregion Action