#include "Enemy.h"
#include <math.h>
#include "EnemyManager.h"
#include "GameManager.h"
#include "Globals.h"

#pragma region Construction
Enemy::Enemy(Managers* managers, std::vector<Tile*> path,std::string name, Sprite* sprite, Vector2D position, Vector2D scale,float maxHealth) :
	managers(managers),name(name), path(path), sprite(sprite), position(position), scale(scale), maxHealth(maxHealth)
{
	dstRect = { (int)this->position.x, (int)this->position.y, (int)this->scale.x, (int)this->scale.y };
	isActive = true;
	health = this->maxHealth;
	originalSpeed = speed;
}
#pragma endregion Construction

#pragma region GameLoop
void Enemy::Start()
{
	if (isActive == true)
	{
		currentStartPosition = GetPosition();
	}
}

void Enemy::Update(float deltaTime)
{
	if (isActive == true)
	{
		MoveToEnd(deltaTime);

		if (isFrozen == true)
		{
			FreezeTimer(deltaTime);
		}
	}
}

void Enemy::Render()
{
	if (isActive == true)
	{
		SDL_RenderCopy(managers->GetRenderer(), sprite->GetTexture(), nullptr, &dstRect);
	}
}
#pragma endregion GameLoop

#pragma region Disable
void Enemy::Reset(Managers* managers, std::vector<Tile*> path, std::string name, Sprite* sprite, Vector2D position, Vector2D scale, float maxHealth) 
{
	Disable();
	this->managers = managers;
	this->path = path;
	this->name = name;
	this->sprite = sprite;
	this->position = position;
	this->scale = scale;
	this->currentStartPosition = this->position;
	this->health = this->maxHealth;

	dstRect = { (int)this->position.x, (int)this->position.y, (int)this->scale.x, (int)this->scale.y };
	this->isActive = true;
}

void Enemy::Disable()
{
	pathIndex = 0;
	movementDelta = 0.0f;
	currentStartPosition = Vector2D::Zero();
	hasReachedEnd = false;
	isFrozen = false;
	hasCountedDeath = false;
	speed = originalSpeed;
	isActive = false;
}
#pragma endregion Disable

#pragma region Move
void Enemy::MoveToEnd(float deltaTime)
{
	if (hasReachedEnd == false)
	{
		movementDelta += speed * deltaTime;

		if (movementDelta >= 1.0f)
		{
			movementDelta = 0;
			currentStartPosition = GetPosition();
			if (pathIndex < path.size() - 1)
			{
				pathIndex += 1;
			}
			else
			{
				hasReachedEnd = true;
				managers->GetManager<GameManager>(ManagerName::GameManager)->ReducePlayerHealth(Globals::dRand(0.3,1.2));
				Disable();
			}
		}
		else
		{
			SetPosition(Vector2D::Lerp(currentStartPosition, path[pathIndex]->GetPosition(), movementDelta));
		}
	}
}
#pragma endregion Move

#pragma region Freeze
void Enemy::Freeze(float freezeTime, float freezeSpeed)
{
	isFrozen = true;
	freezeTimer = 0;
	maxFreezeTime = freezeTime;
	speed = freezeSpeed;
}


bool Enemy::IsFrozen()
{
	return isFrozen;
}

void Enemy::FreezeTimer(float deltaTime)
{
	if (freezeTimer >= maxFreezeTime)
	{
		isFrozen = false;
		speed = originalSpeed;
	}
	freezeTimer += deltaTime;
}
#pragma endregion Freeze

#pragma region Set
void Enemy::SetPosition(Vector2D vector2D)
{
	//Round the values, since SDL_Rect values is in int, otherwise get Stutter
	position = Vector2D(round(vector2D.x), round(vector2D.y));
	dstRect.x = position.x;
	dstRect.y = position.y;
}

void Enemy::SetSpeed(float speed)
{
	this->speed = speed;
}
#pragma endregion Set

#pragma region Damage
void Enemy::TakeDamage(float damage)
{
	health -= damage;
	if (health <= 0 && hasCountedDeath == false)
	{
		managers->GetManager<EnemyManager>(ManagerName::EnemyManager)->IncreaseEnemyDeathCount(1);
		hasCountedDeath = true;
		Disable();
	}
}
#pragma endregion Damage