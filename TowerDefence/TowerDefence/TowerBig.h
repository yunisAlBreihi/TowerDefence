#pragma once
#include "TowerBase.h"

class TowerBig : public TowerBase
{
private:
public:
private:
public:
	TowerBig(Managers* managers, Sprite* sprite, Vector2D position, Vector2D scale);
	void OnShoot() override;
};