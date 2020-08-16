#include "EffectBase.h"
#include <iostream>
//#include "GameManager.h"

EffectBase::EffectBase()
{
}

EffectBase::EffectBase(Managers* managers, BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D startScale, Vector2D endScale) : managers(managers), bulletType(bulletType), sprite(sprite), position(position), startScale(startScale), endScale(endScale)
{
	enemyManager = managers->GetManager<EnemyManager>(ManagerName::EnemyManager);
	startPosition = position;
	endPosition = startPosition - (endScale * 0.5f);
	scale = startScale;
	dstRect = { this->startPosition.x, this->startPosition.y, this->scale.x, this->scale.y };
	startScale = this->scale;
	collider = new Collider(startPosition, startScale.x * 0.5f);
}

EffectBase::~EffectBase()
{
}

void EffectBase::Start()
{
}

void EffectBase::Update(float deltaTime)
{
	if (reachedMaxSize == false)
	{
		LerpExplosionScale(deltaTime);

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
							currentTarget = enemy;
							OnHit(currentTarget);
						}
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
		SDL_RenderCopy(managers->GetRenderer(), sprite->GetTexture(), nullptr, &dstRect);
	}
}

void EffectBase::Destroy()
{
}

void EffectBase::OnHit(EnemyBase* enemy)
{
	if (bulletType == BulletType::Regular)
	{
		enemy->TakeDamage(0.75f);
	}
	else if (bulletType == BulletType::Freezing)
	{
		if (enemy->IsFrozen() == false)
		{
			enemy->TakeDamage(1.0f);
			enemy->Freeze(3.0f, 0.5f);
		}
	}
}

void EffectBase::LerpExplosionScale(float deltaTime)
{
	SetScale(Vector2D::Lerp(startScale, endScale, delta));
	SetPosition(Vector2D::Lerp(startPosition, endPosition, delta));

	//Scales the collider with the expansion of the effect object
	collider->SetPosition(position);
	collider->SetRadius(scale.x * 0.5f);

	if (delta <= 1.0f)
	{
		delta += deltaTime * expandSpeed;
	}
	else
	{
		reachedMaxSize = true;
	}
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
