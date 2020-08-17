#pragma once
#include "EffectBase.h"
class FrostExplosion : public EffectBase
{
private:
public:
private:
public:
	FrostExplosion(Managers* managers,BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D startScale, Vector2D endScale);

	void OnHit(EnemyBase* enemy) override;
};

