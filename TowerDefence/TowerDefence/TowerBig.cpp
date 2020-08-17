#include "TowerBig.h"
#include "GameManager.h"
#include "FrostBullet.h"

TowerBig::TowerBig(Managers* managers, Sprite* sprite, Vector2D position, Vector2D scale)
{
	this->managers = managers;
	enemyManager = managers->GetManager<EnemyManager>(ManagerName::EnemyManager);
	spriteManager = managers->GetManager<SpriteManager>(ManagerName::SpriteManager);
	bulletManager = managers->GetManager<BulletManager>(ManagerName::BulletManager);
	effectsManager = managers->GetManager<EffectsManager>(ManagerName::EffectsManager);
	this->sprite = sprite;
	this->position = position;
	this->scale = scale;
	dstRect = { this->position.x, this->position.y, this->scale.x, this->scale.y };
	collider = new Collider(this->position + Vector2D(GameManager::DEFAULT_SPRITE_SIZE / 2, GameManager::DEFAULT_SPRITE_SIZE / 2), 90.0f);
}

void TowerBig::OnShoot()
{
	FrostBullet* frostBullet = new FrostBullet(managers, spriteManager->GetSprite(SpriteName::startPosition),
		position + Vector2D(GameManager::DEFAULT_SPRITE_SIZE / 2, GameManager::DEFAULT_SPRITE_SIZE / 2),
		currentEnemyTarget->GetPosition() + Vector2D(GameManager::DEFAULT_SPRITE_SIZE / 2, GameManager::DEFAULT_SPRITE_SIZE / 2),
		Vector2D(GameManager::DEFAULT_SPRITE_SIZE / 4, GameManager::DEFAULT_SPRITE_SIZE / 4));

	bulletManager->AddBullet(frostBullet);
}