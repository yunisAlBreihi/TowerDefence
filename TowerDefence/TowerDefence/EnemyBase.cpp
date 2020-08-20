#include "EnemyBase.h"
#include "EnemyManager.h"
#include "GameManager.h"

EnemyBase::EnemyBase()
{
}

EnemyBase::EnemyBase(Managers* managers, std::vector<Tile*> path,std::string name, Sprite* sprite, Vector2D position, Vector2D scale) : managers(managers),name(name), path(path), sprite(sprite), position(position), scale(scale)
{
	dstRect = { this->position.x, this->position.y, this->scale.x, this->scale.y };
	isActive = true;
	health = maxHealth;
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Start()
{
	if (isActive == true)
	{
		currentStartPosition = GetPosition();
		originalSpeed = speed;
	}
}

void EnemyBase::Update(float deltaTime)
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

void EnemyBase::Render()
{
	if (isActive == true)
	{
		SDL_RenderCopy(managers->GetRenderer(), sprite->GetTexture(), nullptr, &dstRect);
	}
}

void EnemyBase::Destroy()
{
}

void EnemyBase::Reset(Managers* managers, std::vector<Tile*> path, std::string name, Sprite* sprite, Vector2D position, Vector2D scale) 
{
	this->managers = managers;
	this->path = path;
	this->name = name;
	this->sprite = sprite;
	this->position = position;
	this->scale = scale;
	this->currentStartPosition = this->position;
	this->health = this->maxHealth;

	dstRect = { this->position.x, this->position.y, this->scale.x, this->scale.y };
	this->isActive = true;
}

void EnemyBase::Disable()
{
	pathIndex = 0;
	delta = 0.0f;
	currentStartPosition = Vector2D::Zero();
	hasReachedEnd = false;
	isFrozen = false;
	speed = originalSpeed;
	isActive = false;
}

void EnemyBase::MoveToEnd(float deltaTime)
{
	if (hasReachedEnd == false)
	{
		delta += speed * deltaTime;

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
				managers->GetManager<GameManager>(ManagerName::GameManager)->ReducePlayerHealth(2);
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
		Disable();
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

	//std::cout << name << " is hit!" << std::endl;
}

void EnemyBase::Freeze(float freezeTime, float freezeSpeed)
{
	isFrozen = true;
	freezeTimer = 0;
	maxFreezeTime = freezeTime;
	speed = freezeSpeed;
}

bool EnemyBase::IsFrozen()
{
	return isFrozen;
}

void EnemyBase::FreezeTimer(float deltaTime)
{
	if (freezeTimer >= maxFreezeTime)
	{
		isFrozen = false;
		speed = originalSpeed;
	}
	freezeTimer += deltaTime;
}
