#include "EnemyBase.h"
EnemyBase::EnemyBase()
{
}

EnemyBase::EnemyBase(SDL_Renderer* renderer, std::vector<Tile*> path, Sprite* sprite, Vector2D position, Vector2D scale) : renderer(renderer), path(path), sprite(sprite), position(position), scale(scale)
{
	dstRect = { this->position.x, this->position.y, this->scale.x, this->scale.y };
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Start()
{
}

void EnemyBase::Update()
{
	if (hasReachedEnd == false)
	{
		timer++;

		if (timer >= timeToMove)
		{
			timer = 0;
			SetPosition(path[pathIndex]->GetPosition());
			if (pathIndex < path.size() - 1)
			{
				pathIndex += 1;
			}
			else
			{
				hasReachedEnd = true;
			}
		}
	}
}

void EnemyBase::Render()
{
	SDL_RenderCopy(renderer, sprite->GetTexture(), nullptr, &dstRect);
}

void EnemyBase::Destroy()
{
}

void EnemyBase::SetPosition(Vector2D vector2D)
{
	position = vector2D;
	dstRect.x = position.x;
	dstRect.y = position.y;
}