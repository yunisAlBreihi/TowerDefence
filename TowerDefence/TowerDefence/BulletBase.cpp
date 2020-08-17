#include "BulletBase.h"
#include "GameManager.h"
#include "Explosion.h"
#include "FrostExplosion.h"

BulletBase::BulletBase()
{
}

BulletBase::BulletBase(Managers* managers, Sprite* sprite, Vector2D startPosition, Vector2D endPosition, Vector2D scale) : managers(managers), sprite(sprite), position(startPosition), endPosition(endPosition), scale(scale)
{
	this->startPosition = startPosition;
	dstRect = { this->position.x, this->position.y, this->scale.x, this->scale.y };
	isMoving = true;
}

BulletBase::~BulletBase()
{
}

void BulletBase::Start()
{
}

void BulletBase::Update(float deltaTime)
{
	if (isMoving == true)
	{
		OnMove(deltaTime);
	}
}

void BulletBase::Render()
{
	if (isMoving == true)
	{
		SDL_RenderCopy(managers->GetRenderer(), sprite->GetTexture(), nullptr, &dstRect);
	}
}

void BulletBase::Destroy()
{
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
		isMoving = false;
	}
}

void BulletBase::StartMoving(Vector2D startPosition, Vector2D endPosition)
{
	if (isMoving == false)
	{
		this->startPosition = startPosition;
		this->endPosition = endPosition;
		isMoving = true;
	}
}