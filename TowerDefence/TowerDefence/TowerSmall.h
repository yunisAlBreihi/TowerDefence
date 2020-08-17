#pragma once
#include "TowerBase.h"

class TowerSmall : public TowerBase
{
private:
public:
private:
public:
	TowerSmall(Managers* managers , Sprite* sprite, Vector2D position, Vector2D scale);

	void OnShoot() override;
};