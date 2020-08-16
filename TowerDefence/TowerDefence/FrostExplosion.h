#pragma once
#include "EffectBase.h"
class FrostExplosion : public EffectBase
{
private:
	float freezeTime = 3.0f;
	float freezeSpeed = 0.5f;
public:
private:
public:
	FrostExplosion(Managers* managers, BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D startScale, Vector2D endScale);

	void OnHit(EnemyBase* enemy) override;
};

