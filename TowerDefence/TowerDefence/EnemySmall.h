#pragma once
#include "EnemyBase.h"

class EnemySmall : public EnemyBase
{
private:

public:

private:

public:
	EnemySmall(SDL_Renderer* renderer, std::vector<Tile*> path, Sprite* sprite, Vector2D position, Vector2D scale);
};