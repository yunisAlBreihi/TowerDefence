#include "EnemyBase.h"
#include "EnemyManager.h"

EnemyBase::EnemyBase()
{
}

EnemyBase::EnemyBase(Managers* managers, std::vector<Tile*> path, Sprite* sprite, Vector2D position, Vector2D scale) : managers(managers), path(path), sprite(sprite), position(position), scale(scale)
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
	if (IsDead() == false)
	{
		MoveToEnd();

		if (isFrozen == true)
		{
			FreezeTimer();
		}
	}
}

void EnemyBase::Render()
{
	if (IsDead() == false)
	{
		SDL_RenderCopy(managers->GetRenderer(), sprite->GetTexture(), nullptr, &dstRect);
	}
}

void EnemyBase::Destroy()
{
}

void EnemyBase::MoveToEnd()
{
	if (hasReachedEnd == false)
	{
		delta += 0.002f * speed;

		if (delta >= 1.0f)
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
			SetPosition(Vector2D::Lerp(currentStartPosition, path[pathIndex]->GetPosition(), delta));
		}
	}
}

bool EnemyBase::IsDead()
{
	if (health <= 0 || hasReachedEnd == true)
	{
		return true;
	}
	return false;
}

void EnemyBase::SetPosition(Vector2D vector2D)
{
	position = vector2D;
	dstRect.x = position.x;
	dstRect.y = position.y;
}

void EnemyBase::SetSpeed(float speed)
{
	this->speed = speed;
}

void EnemyBase::TakeDamage(float damage)
{
	health -= damage;
	if (health <= 0 && hasCountedDeath == false)
	{
		managers->GetManager<EnemyManager>(ManagerName::EnemyManager)->IncreaseEnemyDeathCount(1);
		hasCountedDeath = true;
	}
}

void EnemyBase::Freeze(float freezeTime, float freezeSpeed)
{
	isFrozen = true;
	maxFreezeTime = freezeTime;
	speed = freezeSpeed;
}

bool EnemyBase::IsFrozen()
{
	return isFrozen;
}

void EnemyBase::FreezeTimer()
{
	if (freezeTimer >= maxFreezeTime)
	{
		isFrozen = false;
		speed = originalSpeed;
	}
	freezeTimer += 0.001f;
}
