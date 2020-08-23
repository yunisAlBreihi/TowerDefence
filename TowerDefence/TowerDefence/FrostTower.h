#pragma once
#include "TowerBase.h"

class FrostTower : public TowerBase
{
public:
	FrostTower(Managers* managers, BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D scale);
	~FrostTower();

	void OnShoot() override;
};