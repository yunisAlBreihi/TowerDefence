#include "TowerBase.h"
#include "Globals.h"
#include "BulletBase.h"

TowerBase::TowerBase()
{
}

TowerBase::TowerBase(Managers* managers, BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D scale) :
	managers(managers),bulletType(bulletType), sprite(sprite), position(position), scale(scale)
{
	enemyManager = managers->GetManager<EnemyManager>(ManagerName::EnemyManager);
	spriteManager = managers->GetManager<SpriteManager>(ManagerName::SpriteManager);
	bulletManager = managers->GetManager<BulletManager>(ManagerName::BulletManager);
	effectsManager = managers->GetManager<EffectsManager>(ManagerName::EffectsManager);

	dstRect = { this->position.x, this->position.y, this->scale.x, this->scale.y };
	collider = new Collider(this->position + Vector2D(Globals::DEFAULT_SPRITE_SIZE / 2, Globals::DEFAULT_SPRITE_SIZE / 2), 90.0f);

	isActive = true;
}

TowerBase::~TowerBase()
{
}

void TowerBase::Start()
{
	if (isActive == true)
	{
	}
}

void TowerBase::Update(float deltaTime)
{
	if (isActive == true)
	{
		SetEnemyTarget();
		Shoot(deltaTime);
	}
}

void TowerBase::Render()
{
	if (isActive == true)
	{
		SDL_RenderCopy(managers->GetRenderer(), sprite->GetTexture(), nullptr, &dstRect);

		//Draw a circle for the collisions
		//DrawDebugCircle();
	}

}

void TowerBase::Destroy()
{
}

void TowerBase::Reset(Managers* managers, BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D scale)
{
	this->managers = managers;
	enemyManager = managers->GetManager<EnemyManager>(ManagerName::EnemyManager);
	spriteManager = managers->GetManager<SpriteManager>(ManagerName::SpriteManager);
	bulletManager = managers->GetManager<BulletManager>(ManagerName::BulletManager);
	effectsManager = managers->GetManager<EffectsManager>(ManagerName::EffectsManager);
	this->bulletType = bulletType;
	this->sprite = sprite;
	this->position = position;
	this->scale = scale;
	dstRect = { this->position.x, this->position.y, this->scale.x, this->scale.y };
	collider = new Collider(this->position + Vector2D(Globals::DEFAULT_SPRITE_SIZE / 2, Globals::DEFAULT_SPRITE_SIZE / 2), 90.0f);
	this->isActive = true;
}

void TowerBase::Disable() 
{
	isActive = false;
}

void TowerBase::SetEnemyTarget()
{
	if (currentEnemyTarget == nullptr)
	{
		if (enemyManager->GetEnemies().empty() == false)
		{
			for (std::vector<EnemyBase*> enemies : enemyManager->GetEnemies())
			{
				if (enemies.empty() == false)
				{
					for (EnemyBase* enemy : enemies)
					{
						if (collider->isPointInCircle(enemy->GetPosition() + Vector2D(Globals::DEFAULT_SPRITE_SIZE / 2, Globals::DEFAULT_SPRITE_SIZE / 2)))
						{
							if (enemy->IsDead())
							{
								continue;
							}
							currentEnemyTarget = enemy;
							break;
						}
					}
				}
			}
		}
	}
	else if (currentEnemyTarget->IsDead() == true || 
		collider->isPointInCircle(currentEnemyTarget->GetPosition() + Vector2D(Globals::DEFAULT_SPRITE_SIZE / 2, Globals::DEFAULT_SPRITE_SIZE / 2)) == false)
	{
		currentEnemyTarget = nullptr;
	}
}

void TowerBase::Shoot(float deltaTime)
{
	if (currentEnemyTarget != nullptr)
	{
		shootTimer += deltaTime;

		if (shootTimer >= shootMaxTime)
		{
			OnShoot();
			shootTimer = 0.0f;
		}
	}
}

void TowerBase::SetPosition(Vector2D vector2D)
{
	position = vector2D;
	dstRect.x = position.x;
	dstRect.y = position.y;
}

void TowerBase::DrawDebugCircle()
{
	if (collisionRadius > 0)
	{
		for (size_t i = 0; i < 360; i += debugCircleQuality)
		{
			circlePosition = Vector2D(GetPosition().x + collisionRadius * std::cos(i), GetPosition().y + collisionRadius * std::sin(i));
			SDL_SetRenderDrawColor(managers->GetRenderer(), 230, 0, 126, 255);
			SDL_RenderDrawPoint(managers->GetRenderer(), circlePosition.x + scale.x / 2, circlePosition.y + scale.y / 2);
			SDL_SetRenderDrawColor(managers->GetRenderer(), 0, 0, 0, 255);
		}
	}
}
