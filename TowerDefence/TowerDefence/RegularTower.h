#pragma once
#include "TowerBase.h"

class RegularTower : public TowerBase
{
public:
	RegularTower(BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D scale);
	~RegularTower();

	void OnShoot() override;
};