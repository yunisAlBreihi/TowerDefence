#include "EffectBase.h"
#include <iostream>
#include "GameManager.h"

EffectBase::EffectBase(SDL_Renderer* renderer,EnemyManager* enemyManager,BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D startScale, Vector2D endScale) : renderer(renderer),enemyManager(enemyManager),bulletType(bulletType), sprite(sprite), position(position), startScale(startScale), endScale(endScale)
{
	startPosition = position;
	endPosition = startPosition - (endScale * 0.5f);
	scale = startScale;
	dstRect = { this->startPosition.x, this->startPosition.y, this->scale.x, this->scale.y };
	startScale = this->scale;
	collider = new Collider(startPosition,  startScale.x * 0.5f);
}

void EffectBase::Start()
{
}

void EffectBase::Update()
{
	if (reachedMaxSize == false)
	{
		Expand();

		for (std::vector<EnemyBase*> enemies : enemyManager->GetEnemies())
		{
			for (EnemyBase* enemy : enemies)
			{
				if (enemy->IsDead() == false)
				{
					if (collider->isPointInCircle(position, enemy->GetPosition(), scale.x * 0.5f))
					{
						//Makes sure the enemy can only be hit once
						if (enemy != currentTarget)
						{
							if (bulletType == BulletType::Regular)
							{
								enemy->TakeDamage(1.0f);
							}
							else if (bulletType == BulletType::Freezing)
							{
								if (enemy->IsFrozen() == false)
								{
									enemy->Freeze(3.0f, 0.5f);
								}
							}

							currentTarget = enemy;
						}
						//std::cout << "Enemy is inside explosion!" << std::endl;
					}
				}
			}
		}
	}
}

void EffectBase::Render()
{
	if (reachedMaxSize == false)
	{
		SDL_RenderCopy(renderer, sprite->GetTexture(), nullptr, &dstRect);
	}
}

void EffectBase::Destroy()
{
}

void EffectBase::SetPosition(Vector2D position)
{
	this->position = position;
	dstRect.x = this->position.x;
	dstRect.y = this->position.y;
}

void EffectBase::SetScale(Vector2D scale)
{
	this->scale = scale;
	dstRect.w = this->scale.x;
	dstRect.h = this->scale.y;
}

void EffectBase::Expand()
{
	SetScale(Vector2D::Lerp(startScale, endScale, delta));
	SetPosition(Vector2D::Lerp(startPosition, endPosition, delta));

	//Scales the collider with the effect
	collider->SetPosition(position);
	collider->SetRadius(scale.x * 0.5f);

	if (delta <= 1.0f)
	{
		delta += 0.003f;
	}
	else
	{
		reachedMaxSize = true;
	}
}
