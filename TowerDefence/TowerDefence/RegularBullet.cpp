#include "RegularBullet.h"
#include "Explosion.h"
#include "Globals.h"

RegularBullet::RegularBullet(Managers* managers, BulletType bulletType, Sprite* sprite, Vector2D startPosition, Vector2D endPosition, Vector2D scale)
{
	this->managers = managers;
	this->bulletType = bulletType;
	this->sprite = sprite;
	this->position = startPosition;
	this->startPosition = startPosition;
	this->endPosition = endPosition;
	this->scale = scale;

	dstRect = { (int)this->position.x, (int)this->position.y, (int)this->scale.x, (int)this->scale.y };
	isActive = true;
}

RegularBullet::~RegularBullet()
{
}

void RegularBullet::OnReachedDestination()
{
	EffectsManager* effectsManager = managers->GetManager<EffectsManager>(ManagerName::EffectsManager);
	Explosion* explosion = (Explosion*)effectsManager->GetInactiveEffectOfType(bulletType);
	if (explosion == nullptr)
	{
		explosion = new Explosion(managers, bulletType, sprite, position, Vector2D::Zero(), Vector2D::One() * (Globals::DEFAULT_SPRITE_SIZE * 2.0f));
		effectsManager->AddEffect(explosion);
	}
	else
	{
		explosion->Reset(managers, bulletType, sprite, position, Vector2D::Zero(), Vector2D::One() * (Globals::DEFAULT_SPRITE_SIZE * 2.0f));
	}
}