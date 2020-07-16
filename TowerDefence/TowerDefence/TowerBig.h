#pragma once
#include "TowerBase.h"

class TowerBig : public TowerBase
{
private:
public:
private:
public:
	TowerBig(SDL_Renderer* renderer, EnemyManager* enemyManager, SpriteManager* spriteManager, BulletManager* bulletManager, EffectsManager* effectsManager,BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D scale);
};