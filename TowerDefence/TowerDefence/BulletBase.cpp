#include "BulletBase.h"

//BulletBase::BulletBase()
//{
//}

BulletBase::BulletBase(SDL_Renderer* renderer, Sprite* sprite, Vector2D scale, Vector2D position) : renderer(renderer), sprite(sprite), scale(scale), position(position)
{
	dstRect = { this->position.x, this->position.y, this->scale.x, this->scale.y };
}

BulletBase::~BulletBase()
{
}

void BulletBase::Start()
{
}

void BulletBase::Update()
{
	if (isMoving == true)
	{
		delta += 0.001f;
		SetPosition(Vector2D::Lerp(startPosition, endPosition, delta));
	}
}

void BulletBase::Render()
{
	SDL_RenderCopy(renderer, sprite->GetTexture(), nullptr, &dstRect);
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

void BulletBase::StartMoving(Vector2D startPosition, Vector2D endPosition)
{
	if (isMoving == false)
	{
		this->startPosition = startPosition;
		this->endPosition = endPosition;
		isMoving = true;
	}
}

