#include "Enemy.h"
#include "EnemyManager.h"
#include "GameManager.h"

Enemy::Enemy(Managers* managers, std::vector<Tile*> path,std::string name, Sprite* sprite, Vector2D position, Vector2D scale,float maxHealth) : managers(managers),name(name), path(path), sprite(sprite), position(position), scale(scale), maxHealth(maxHealth)
{
	dstRect = { (int)this->position.x, (int)this->position.y, (int)this->scale.x, (int)this->scale.y };
	isActive = true;
	health = this->maxHealth;
}

Enemy::~Enemy()
{
}

void Enemy::Start()
{
	if (isActive == true)
	{
		currentStartPosition = GetPosition();
		originalSpeed = speed;
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

void Enemy::Destroy()
{
}

void Enemy::Reset(Managers* managers, std::vector<Tile*> path, std::string name, Sprite* sprite, Vector2D position, Vector2D scale, float maxHealth) 
{
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
	delta = 0.0f;
	currentStartPosition = Vector2D::Zero();
	hasReachedEnd = false;
	isFrozen = false;
	hasCountedDeath = false;
	speed = originalSpeed;
	isActive = false;
}

void Enemy::MoveToEnd(float deltaTime)
{
	if (hasReachedEnd == false)
	{
		delta += speed * deltaTime;

		if (delta >= 1.0f + deltaTime)
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
				managers->GetManager<GameManager>(ManagerName::GameManager)->ReducePlayerHealth(1);
			}
		}
		else
		{
			SetPosition(Vector2D::Lerp(currentStartPosition, path[pathIndex]->GetPosition(), delta));
		}
	}
}

bool Enemy::IsDead()
{
	if (health <= 0 || hasReachedEnd == true)
	{
		Disable();
		return true;
	}
	return false;
}

void Enemy::SetPosition(Vector2D vector2D)
{
	position = vector2D;
	dstRect.x = position.x;
	dstRect.y = position.y;
}

void Enemy::SetSpeed(float speed)
{
	this->speed = speed;
}

void Enemy::TakeDamage(float damage)
{
	health -= damage;
	if (health <= 0 && hasCountedDeath == false)
	{
		managers->GetManager<EnemyManager>(ManagerName::EnemyManager)->IncreaseEnemyDeathCount(1);
		hasCountedDeath = true;
	}

	//std::cout << name << " is hit!" << std::endl;
}

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
