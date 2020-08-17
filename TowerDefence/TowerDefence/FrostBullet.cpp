#include "FrostBullet.h"
#include "FrostExplosion.h"
#include "GameManager.h"

FrostBullet::FrostBullet(Managers* managers, Sprite* sprite, Vector2D startPosition, Vector2D endPosition, Vector2D scale)
{
	this->managers = managers;
	this->sprite = sprite;
	this->position = startPosition;
	this->startPosition = startPosition;
	this-> endPosition = endPosition;
	this->scale = scale;

	dstRect = { this->position.x, this->position.y, this->scale.x, this->scale.y };
	isMoving = true;
}

FrostBullet::~FrostBullet()
{
}

void FrostBullet::OnReachedDestination()
{
	FrostExplosion* frostExplosion = new FrostExplosion(managers, sprite, position, Vector2D::Zero(), Vector2D::One() * (GameManager::DEFAULT_SPRITE_SIZE * 2.0f));
	managers->GetManager<EffectsManager>(ManagerName::EffectsManager)->AddEffect(frostExplosion);
}