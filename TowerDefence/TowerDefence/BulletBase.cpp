#include "BulletBase.h"
#include "GameManager.h"
#include "Explosion.h"
#include "FrostExplosion.h"

BulletBase::BulletBase()
{
}

BulletBase::BulletBase(Managers* managers, BulletType bulletType, Sprite* sprite, Vector2D startPosition, Vector2D endPosition, Vector2D scale) : managers(managers), bulletType(bulletType), sprite(sprite), position(startPosition), endPosition(endPosition), scale(scale)
{
	this->startPosition = startPosition;
	dstRect = { this->position.x, this->position.y, this->scale.x, this->scale.y };
	isActive = true;
}

BulletBase::~BulletBase()
{
}

void BulletBase::Start()
{
}

void BulletBase::Update(float deltaTime)
{
	if (isActive == true)
	{
		OnMove(deltaTime);
	}
}

void BulletBase::Render()
{
	if (isActive == true)
	{
		SDL_RenderCopy(managers->GetRenderer(), sprite->GetTexture(), nullptr, &dstRect);
	}
}

void BulletBase::Destroy()
{
}

void BulletBase::Reset(Managers* managers, BulletType bulletType, Sprite* sprite, Vector2D startPosition, Vector2D endPosition, Vector2D scale)
{
	this->managers = managers;
	this->bulletType = bulletType;
	this->sprite = sprite;
	this->position = startPosition;
	this->startPosition = startPosition;
	this->endPosition = endPosition;
	this->scale = scale;

	dstRect = { this->position.x, this->position.y, this->scale.x, this->scale.y };
	isActive = true;
}

void BulletBase::Clear()
{
	movementDelta = 0.0f;
	isActive = false;
}

void BulletBase::SetPosition(Vector2D vector2D)
{
	position = vector2D;
	dstRect.x = position.x;
	dstRect.y = position.y;
}

void BulletBase::OnMove(float deltaTime)
{
	SetPosition(Vector2D::Lerp(startPosition, endPosition, movementDelta));
	if (movementDelta <= 1.0f)
	{
		movementDelta += speed * deltaTime;
	}
	else
	{
		OnReachedDestination();
		Clear();
	}
}