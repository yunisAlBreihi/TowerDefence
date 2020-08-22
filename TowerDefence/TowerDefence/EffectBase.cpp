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
	dstRect = { (int)this->startPosition.x, (int)this->startPosition.y, (int)this->scale.x, (int)this->scale.y };
	collider = new Collider(startPosition, startScale.x * 0.5f);
	enemiesHit = std::vector<Enemy*>();

	isActive = true;
}

EffectBase::~EffectBase()
{
}

void EffectBase::Start()
{
	if (isActive == true)
	{
	}
}

void EffectBase::Update(float deltaTime)
{
	if (isActive == true)
	{
		Expand(deltaTime);
	}
}

void EffectBase::Render()
{
	if (isActive == true)
	{
		SDL_RenderCopy(managers->GetRenderer(), sprite->GetTexture(), nullptr, &dstRect);

		////Draw the colliders radius
		//collider->DrawDebugCircle(managers->GetRenderer());
	}
}

void EffectBase::Destroy()
{
}

void EffectBase::Reset(Managers* managers, BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D startScale, Vector2D endScale)
{
	this->managers = managers;
	this->bulletType = bulletType;
	this->sprite = sprite;
	this->position = position;
	this->startScale = startScale;
	this->endScale = endScale;

	enemyManager = managers->GetManager<EnemyManager>(ManagerName::EnemyManager);
	startPosition = position;
	endPosition = startPosition - (endScale * 0.5f);
	scale = startScale;
	dstRect = { (int)this->startPosition.x, (int)this->startPosition.y, (int)this->scale.x, (int)this->scale.y };
	collider = new Collider(startPosition, startScale.x * 0.5f);

	isActive = true;
}

void EffectBase::Clear()
{
	isActive = false;
	delta = 0;
	enemiesHit.clear();
}

void EffectBase::Expand(float deltaTime)
{
	for (Enemy* enemy : enemyManager->GetEnemies())
	{
		if (enemy->IsDead() == false)
		{
			if (collider->isPointInCircle(enemy->GetPosition()))
			{
				//Makes sure the enemy can only be hit once
				if (enemiesHit.empty() == true)
				{
					OnHit(enemy);
					enemiesHit.push_back(enemy);
				}
				else
				{
					auto it = std::find(enemiesHit.begin(), enemiesHit.end(), enemy);

					if (it == enemiesHit.end())
					{
						OnHit(enemy);
						enemiesHit.push_back(enemy);
					}
				}

			}
		}
	}

	LerpExplosionScale(deltaTime);
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
		Clear();
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
