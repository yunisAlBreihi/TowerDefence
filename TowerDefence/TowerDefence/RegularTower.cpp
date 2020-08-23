#include "RegularTower.h"
#include "RegularBullet.h"
#include "Globals.h"

#pragma region Construction
RegularTower::RegularTower(Managers* managers, BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D scale)
{
	this->managers = managers;
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

RegularTower::~RegularTower()
{
}
#pragma endregion Construction

#pragma region Shoot
void RegularTower::OnShoot()
{
	BulletManager* bulletManager = managers->GetManager<BulletManager>(ManagerName::BulletManager);
	RegularBullet* regularBullet = (RegularBullet*)bulletManager->GetInactiveBulletOfType(bulletType);
	if (regularBullet == nullptr)
	{
		regularBullet = new RegularBullet(bulletType, spriteManager->GetSprite(SpriteName::EnemyBase),
			position + Vector2D(Globals::DEFAULT_SPRITE_SIZE / 2, Globals::DEFAULT_SPRITE_SIZE / 2),
			currentEnemyTarget->GetPosition() + Vector2D(Globals::DEFAULT_SPRITE_SIZE / 2, Globals::DEFAULT_SPRITE_SIZE / 2),
			Vector2D(Globals::DEFAULT_SPRITE_SIZE / 4, Globals::DEFAULT_SPRITE_SIZE / 4));
		bulletManager->AddBullet(regularBullet);
	}
	else
	{
		regularBullet->Reset(bulletType, spriteManager->GetSprite(SpriteName::EnemyBase),
			position + Vector2D(Globals::DEFAULT_SPRITE_SIZE / 2, Globals::DEFAULT_SPRITE_SIZE / 2),
			currentEnemyTarget->GetPosition() + Vector2D(Globals::DEFAULT_SPRITE_SIZE / 2, Globals::DEFAULT_SPRITE_SIZE / 2),
			Vector2D(Globals::DEFAULT_SPRITE_SIZE / 4, Globals::DEFAULT_SPRITE_SIZE / 4));
	}
}
#pragma endregion Shoot