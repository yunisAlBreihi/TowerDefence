#pragma once
#include "BulletBase.h"
class FrostBullet : public BulletBase
{
private:
public:
private:
public:
	FrostBullet(Managers* managers, Sprite* sprite, Vector2D startPosition, Vector2D endPosition, Vector2D scale);
	~FrostBullet();
	void OnReachedDestination() override;
};

