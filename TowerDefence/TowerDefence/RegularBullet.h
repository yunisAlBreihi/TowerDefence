#pragma once
#include "BulletBase.h"

class RegularBullet : public BulletBase
{
public:
	RegularBullet(BulletType bulletType, Sprite* sprite, Vector2D startPosition, Vector2D endPosition, Vector2D scale);

	void OnReachedDestination() override;
};