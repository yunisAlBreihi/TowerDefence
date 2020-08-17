#pragma once
#include "BulletBase.h"
class RegularBullet : public BulletBase
{
private:
public:
private:
public:
	RegularBullet(Managers* managers , Sprite* sprite, Vector2D startPosition, Vector2D endPosition, Vector2D scale);
	~RegularBullet();
	void OnReachedDestination() override;
};