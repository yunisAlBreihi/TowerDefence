#pragma once
#include "EffectBase.h"
class Explosion : public EffectBase
{
private:
public:
private:
public:
	Explosion(Managers* managers , Sprite* sprite, Vector2D position, Vector2D startScale, Vector2D endScale);

	void OnHit(EnemyBase* enemy) override;
};