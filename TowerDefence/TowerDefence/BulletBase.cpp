#include "BulletBase.h"

#pragma region Construction
BulletBase::BulletBase()
{
}

BulletBase::BulletBase(BulletType bulletType, Sprite* sprite, Vector2D startPosition, Vector2D endPosition, Vector2D scale) : bulletType(bulletType), sprite(sprite), position(startPosition), endPosition(endPosition), scale(scale)
{
	managers = Managers::GetInstance();
	this->startPosition = startPosition;
	dstRect = { (int)this->position.x, (int)this->position.y, (int)this->scale.x, (int)this->scale.y };
	isActive = true;
}

BulletBase::~BulletBase()
{
}
#pragma endregion Construction

#pragma region GameLoop
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
#pragma endregion GameLoop

#pragma region Disable
void BulletBase::Reset(BulletType bulletType, Sprite* sprite, Vector2D startPosition, Vector2D endPosition, Vector2D scale)
{
	managers = Managers::GetInstance();
	this->bulletType = bulletType;
	this->sprite = sprite;
	this->position = startPosition;
	this->startPosition = startPosition;
	this->endPosition = endPosition;
	this->scale = scale;

	dstRect = { (int)this->position.x, (int)this->position.y, (int)this->scale.x, (int)this->scale.y };
	isActive = true;
}

void BulletBase::Clear()
{
	movementDelta = 0.0f;
	isActive = false;
}
#pragma endregion Disable

#pragma region Set
void BulletBase::SetPosition(Vector2D vector2D)
{
	//Round the values, since SDL_Rect is in int, otherwise get Stutter
	position = Vector2D(round(vector2D.x),round(vector2D.y));
	dstRect.x = position.x;
	dstRect.y = position.y;
}
#pragma endregion Set

#pragma region Move
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
#pragma endregion Move