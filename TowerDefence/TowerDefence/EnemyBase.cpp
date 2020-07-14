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
	currentStartPosition = GetPosition();
}

void EnemyBase::Update()
{
	if (hasReachedEnd == false)
	{
		delta+= 0.002f;

		if (delta >= 1)
		{
			delta = 0;
			currentStartPosition = GetPosition();
			if (pathIndex < path.size() - 1)
			{
				pathIndex += 1;
			}
			else
			{
				hasReachedEnd = true;
			}
		}
		else
		{
			SetPosition(Vector2D::Lerp(currentStartPosition,path[pathIndex]->GetPosition(), delta));
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