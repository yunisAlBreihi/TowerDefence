#pragma once
#include "ExplosionBase.h"
class FrostExplosion : public ExplosionBase
{
public:
	FrostExplosion(BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D startScale, Vector2D endScale);
	~FrostExplosion();

	void OnHit(Enemy* enemy) override;
};