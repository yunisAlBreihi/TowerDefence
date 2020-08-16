#include "BulletBase.h"
#include "GameManager.h"
#include "Explosion.h"
#include "FrostExplosion.h"

BulletBase::BulletBase()
{
}

BulletBase::BulletBase(Managers* managers,BulletType bulletType, Sprite* sprite, Vector2D startPosition, Vector2D endPosition, Vector2D scale) : managers(managers),bulletType(bulletType), sprite(sprite), position(startPosition), endPosition(endPosition), scale(scale)
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
		SetPosition(Vector2D::Lerp(startPosition, endPosition, movementDelta));
		if (movementDelta <= 1.0f)
		{
			movementDelta += speed * deltaTime;
		}
		else
		{
			isMoving = false;
			if (bulletType == BulletType::Regular)
			{
				Explosion* explosion = new Explosion(managers, bulletType, sprite, position, Vector2D::Zero(), Vector2D::One() * (GameManager::DEFAULT_SPRITE_SIZE * 2.0f));
				managers->GetManager<EffectsManager>(ManagerName::EffectsManager)->AddEffect(explosion);
			}
			else if (bulletType == BulletType::Freezing)
			{
				FrostExplosion* frostExplosion = new FrostExplosion(managers, bulletType, sprite, position, Vector2D::Zero(), Vector2D::One() * (GameManager::DEFAULT_SPRITE_SIZE * 2.0f));
				managers->GetManager<EffectsManager>(ManagerName::EffectsManager)->AddEffect(frostExplosion);
			}
		}
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

void BulletBase::StartMoving(Vector2D startPosition, Vector2D endPosition)
{
	if (isMoving == false)
	{
		this->startPosition = startPosition;
		this->endPosition = endPosition;
		isMoving = true;
	}
}

