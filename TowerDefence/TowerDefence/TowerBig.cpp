#include "TowerBig.h"
#include "Globals.h"
#include "FrostBullet.h"

TowerBig::TowerBig(Managers* managers, BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D scale)
{
	this->managers = managers;
	enemyManager = managers->GetManager<EnemyManager>(ManagerName::EnemyManager);
	spriteManager = managers->GetManager<SpriteManager>(ManagerName::SpriteManager);
	bulletManager = managers->GetManager<BulletManager>(ManagerName::BulletManager);
	effectsManager = managers->GetManager<EffectsManager>(ManagerName::EffectsManager);
	this->bulletType = bulletType;
	this->sprite = sprite;
	this->position = position;
	this->scale = scale;
	dstRect = { this->position.x, this->position.y, this->scale.x, this->scale.y };
	collider = new Collider(this->position + Vector2D(Globals::DEFAULT_SPRITE_SIZE / 2, Globals::DEFAULT_SPRITE_SIZE / 2), 90.0f);
}

void TowerBig::OnShoot()
{
	BulletManager* bulletManager = managers->GetManager<BulletManager>(ManagerName::BulletManager);
	FrostBullet* frostBullet = (FrostBullet*)bulletManager->GetInactiveBulletOfType(bulletType);
	if (frostBullet == nullptr)
	{
		frostBullet = new FrostBullet(managers, bulletType, spriteManager->GetSprite(SpriteName::startPosition),
			position + Vector2D(Globals::DEFAULT_SPRITE_SIZE / 2, Globals::DEFAULT_SPRITE_SIZE / 2),
			currentEnemyTarget->GetPosition() + Vector2D(Globals::DEFAULT_SPRITE_SIZE / 2, Globals::DEFAULT_SPRITE_SIZE / 2),
			Vector2D(Globals::DEFAULT_SPRITE_SIZE / 4, Globals::DEFAULT_SPRITE_SIZE / 4));
		bulletManager->AddBullet(frostBullet);
	}
	else
	{
		frostBullet->Reset(managers, bulletType, spriteManager->GetSprite(SpriteName::startPosition),
			position + Vector2D(Globals::DEFAULT_SPRITE_SIZE / 2, Globals::DEFAULT_SPRITE_SIZE / 2),
			currentEnemyTarget->GetPosition() + Vector2D(Globals::DEFAULT_SPRITE_SIZE / 2, Globals::DEFAULT_SPRITE_SIZE / 2),
			Vector2D(Globals::DEFAULT_SPRITE_SIZE / 4, Globals::DEFAULT_SPRITE_SIZE / 4));
	}
}