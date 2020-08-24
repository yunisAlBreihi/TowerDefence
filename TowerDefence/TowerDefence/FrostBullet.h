#pragma once
#include "BulletBase.h"

class FrostBullet : public BulletBase
{
public:
	FrostBullet(BulletType bulletType, Sprite* sprite, Vector2D startPosition, Vector2D endPosition, Vector2D scale);

	void OnReachedDestination() override;
};