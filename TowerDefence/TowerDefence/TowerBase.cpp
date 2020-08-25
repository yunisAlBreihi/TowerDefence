#include "TowerBase.h"
#include "Globals.h"
#include "BulletBase.h"

#pragma region Construction
TowerBase::TowerBase()
{
}

TowerBase::TowerBase(BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D scale) : bulletType(bulletType), sprite(sprite), position(position), scale(scale)
{
	managers = Managers::GetInstance();
	enemyManager = managers->GetManager<EnemyManager>(ManagerName::EnemyManager);
	spriteManager = managers->GetManager<SpriteManager>(ManagerName::SpriteManager);
	bulletManager = managers->GetManager<BulletManager>(ManagerName::BulletManager);
	effectsManager = managers->GetManager<EffectManager>(ManagerName::EffectsManager);

	dstRect = { (int)this->position.x, (int)this->position.y, (int)this->scale.x, (int)this->scale.y };
	collider = new Collider(this->position + Vector2D(Globals::DEFAULT_SPRITE_SIZE / 2, Globals::DEFAULT_SPRITE_SIZE / 2), 90.0f);

	shootMaxTime = (float)Globals::dRand(0.7, 1.5);
	isActive = true;
}

TowerBase::~TowerBase()
{
	delete collider;
}
#pragma endregion Construction

#pragma region GameLoop
void TowerBase::Start()
{
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
	}

}
#pragma endregion GameLoop

#pragma region Disable
void TowerBase::Reset(BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D scale)
{
	enemyManager = managers->GetManager<EnemyManager>(ManagerName::EnemyManager);
	spriteManager = managers->GetManager<SpriteManager>(ManagerName::SpriteManager);
	bulletManager = managers->GetManager<BulletManager>(ManagerName::BulletManager);
	effectsManager = managers->GetManager<EffectManager>(ManagerName::EffectsManager);
	this->bulletType = bulletType;
	this->sprite = sprite;
	this->position = position;
	this->scale = scale;
	dstRect = { (int)this->position.x, (int)this->position.y, (int)this->scale.x, (int)this->scale.y };
	collider = new Collider(this->position + Vector2D(Globals::DEFAULT_SPRITE_SIZE / 2, Globals::DEFAULT_SPRITE_SIZE / 2), 90.0f);
	this->isActive = true;
}

void TowerBase::Disable()
{
	isActive = false;
}
#pragma endregion Disable

#pragma region Shoot
void TowerBase::SetEnemyTarget()
{
	//Find new target
	if (currentEnemyTarget == nullptr)
	{
		for (const auto& enemy : enemyManager->GetEnemies())
		{
			if (collider->isPointInCircle(enemy->GetPosition() + Vector2D(Globals::DEFAULT_SPRITE_SIZE / 2, Globals::DEFAULT_SPRITE_SIZE / 2)))
			{
				if (enemy->IsActive() == false)
				{
					continue;
				}
				currentEnemyTarget = enemy;
				break;
			}
		}
	}
	//If target already exist, remove the reference
	else if (currentEnemyTarget->IsActive() == false ||
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
			shootMaxTime = (float)Globals::dRand(0.7, 1.5);
			shootTimer = 0.0f;
		}
	}
}
#pragma endregion Shoot

#pragma region Set
void TowerBase::SetPosition(Vector2D position)
{
	this->position = {round(position.x),round(position.y)};
	dstRect.x = (int)this->position.x;
	dstRect.y = (int)this->position.y;
}
#pragma endregion Set

#pragma region Debug
void TowerBase::DrawDebugRange()
{
	if (collisionRadius > 0)
	{
		for (unsigned int i = 0; i < 360; i += debugCircleQuality)
		{
			circlePosition = Vector2D(GetPosition().x + (float)(collisionRadius * std::cos(i)), GetPosition().y + (float)(collisionRadius * std::sin(i)));
			SDL_SetRenderDrawColor(managers->GetRenderer(), 230, 0, 126, 255);
			SDL_RenderDrawPoint(managers->GetRenderer(), (int)(circlePosition.x + round(scale.x / 2)), (int)(circlePosition.y + round(scale.y / 2)));
			SDL_SetRenderDrawColor(managers->GetRenderer(), 0, 0, 0, 255);
		}
	}
}
#pragma endregion Debug