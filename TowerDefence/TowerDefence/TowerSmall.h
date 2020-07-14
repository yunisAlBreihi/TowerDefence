#pragma once
#include "TowerBase.h"

class TowerSmall : public TowerBase
{
private:
public:
private:
public:
	TowerSmall(SDL_Renderer* renderer, EnemyManager* enemyManager, SpriteManager* spriteManager,BulletManager* bulletManager, Sprite* sprite, Vector2D position, Vector2D scale);
};