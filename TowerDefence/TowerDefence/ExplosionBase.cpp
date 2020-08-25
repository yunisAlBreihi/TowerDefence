#include "ExplosionBase.h"
#include <iostream>

#pragma region Construction
ExplosionBase::ExplosionBase()
{
}

ExplosionBase::ExplosionBase(BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D startScale, Vector2D endScale) :
	bulletType(bulletType), sprite(sprite), position(position), startScale(startScale), endScale(endScale)
{
	managers = Managers::GetInstance();
	enemyManager = managers->GetManager<EnemyManager>(ManagerName::EnemyManager);
	startPosition = position;
	endPosition = startPosition - (endScale * 0.5f);
	scale = startScale;
	dstRect = { (int)this->startPosition.x, (int)this->startPosition.y, (int)this->scale.x, (int)this->scale.y };
	collider = new Collider(startPosition, startScale.x * 0.5f);
	enemiesHit = std::vector<Enemy*>();

	isActive = true;
}

ExplosionBase::~ExplosionBase()
{
}
#pragma endregion Construction

#pragma region GameLoop
void ExplosionBase::Start()
{
}

void ExplosionBase::Update(float deltaTime)
{
	if (isActive == true)
	{
		Expand(deltaTime);
	}
}

void ExplosionBase::Render()
{
	if (isActive == true)
	{
		SDL_RenderCopy(managers->GetRenderer(), sprite->GetTexture(), nullptr, &dstRect);

		////Draw the colliders radius
		//collider->DrawDebugCircle(managers->GetRenderer());
	}
}
#pragma endregion GameLoop

#pragma region Disable
void ExplosionBase::Reset(BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D startScale, Vector2D endScale)
{
	Disable();
	managers = Managers::GetInstance();
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

void ExplosionBase::Disable()
{
	isActive = false;
	expansionDelta = 0;
	enemiesHit.clear();
}
#pragma endregion Disable

#pragma region ExpandExplosion
void ExplosionBase::Expand(float deltaTime)
{
	for (const auto& enemy : enemyManager->GetEnemies())
	{
		if (enemy->IsActive() == true)
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

void ExplosionBase::LerpExplosionScale(float deltaTime)
{
	SetScale(Vector2D::Lerp(startScale, endScale, expansionDelta));
	SetPosition(Vector2D::Lerp(startPosition, endPosition, expansionDelta));

	//Scales the collider with the expansion of the effect object
	collider->SetPosition(position);
	collider->SetRadius(scale.x * 0.5f);

	if (expansionDelta <= 1.0f)
	{
		expansionDelta += deltaTime * expandSpeed;
	}
	else
	{
		Disable();
	}
}
#pragma endregion ExpandExplosion

#pragma region Set
void ExplosionBase::SetPosition(Vector2D position)
{
	//Round the values, since SDL_Rect is in int, otherwise get Stutter
	this->position = { round(position.x), round(position.y) };
	dstRect.x = (int)this->position.x;
	dstRect.y = (int)this->position.y;
}

void ExplosionBase::SetScale(Vector2D scale)
{
	//Round the values, since SDL_Rect is in int, otherwise get Stutter
	this->scale = { round(scale.x), round(scale.y) };
	dstRect.w = (int)this->scale.x;
	dstRect.h = (int)this->scale.y;
}
#pragma endregion Set
