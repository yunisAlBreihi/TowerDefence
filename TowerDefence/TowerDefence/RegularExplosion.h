#pragma once
#include "ExplosionBase.h"
class RegularExplosion : public ExplosionBase
{
public:
	RegularExplosion(BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D startScale, Vector2D endScale);

	void OnHit(Enemy* enemy) override;
};