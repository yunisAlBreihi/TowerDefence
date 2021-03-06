#include "FrostTower.h"
#include "FrostBullet.h"
#include "Globals.h"

#pragma region Construction
FrostTower::FrostTower(BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D scale)
{
	managers = Managers::GetInstance();
	enemyManager = managers->GetManager<EnemyManager>(ManagerName::EnemyManager);
	spriteManager = managers->GetManager<SpriteManager>(ManagerName::SpriteManager);
	bulletManager = managers->GetManager<BulletManager>(ManagerName::BulletManager);
	effectsManager = managers->GetManager<EffectManager>(ManagerName::EffectsManager);

	this->bulletType = bulletType;
	this->sprite = sprite;
	this->position = position;
	this->scale = scale;
	dstRect = { (int)this->position.x, (int)this->position.y, (int)this->scale.x, (int)this->scale.y };
	collider = new Collider(this->position + Vector2D(Globals::DEFAULT_SPRITE_SIZE / 2, Globals::DEFAULT_SPRITE_SIZE / 2), 90.0f);
	this->isActive = true;
}
FrostTower::~FrostTower()
{
	delete collider;
}
#pragma endregion Construction

#pragma region Shoot
void FrostTower::OnShoot()
{
	BulletManager* bulletManager = managers->GetManager<BulletManager>(ManagerName::BulletManager);
	FrostBullet* frostBullet = (FrostBullet*)bulletManager->GetInactiveBulletOfType(bulletType);
	if (frostBullet == nullptr)
	{
		frostBullet = new FrostBullet(bulletType, spriteManager->GetSprite(SpriteName::FrostBullet),
			position + Vector2D(Globals::DEFAULT_SPRITE_SIZE / 2, Globals::DEFAULT_SPRITE_SIZE / 2),
			currentEnemyTarget->GetPosition() + Vector2D(Globals::DEFAULT_SPRITE_SIZE / 2, Globals::DEFAULT_SPRITE_SIZE / 2),
			Vector2D(Globals::DEFAULT_SPRITE_SIZE / 4, Globals::DEFAULT_SPRITE_SIZE / 4));
		bulletManager->AddBullet(frostBullet);
	}
	else
	{
		frostBullet->Reset(bulletType, spriteManager->GetSprite(SpriteName::FrostBullet),
			position + Vector2D(Globals::DEFAULT_SPRITE_SIZE / 2, Globals::DEFAULT_SPRITE_SIZE / 2),
			currentEnemyTarget->GetPosition() + Vector2D(Globals::DEFAULT_SPRITE_SIZE / 2, Globals::DEFAULT_SPRITE_SIZE / 2),
			Vector2D(Globals::DEFAULT_SPRITE_SIZE / 4, Globals::DEFAULT_SPRITE_SIZE / 4));
	}
}
#pragma endregion Shoot