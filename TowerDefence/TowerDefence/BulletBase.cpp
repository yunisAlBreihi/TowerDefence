#include "BulletBase.h"
#include "GameManager.h"

//BulletBase::BulletBase()
//{
//}

BulletBase::BulletBase()
{
}

BulletBase::BulletBase(SDL_Renderer* renderer,EnemyManager* enemyManager, EffectsManager* effectsManager, Sprite* sprite, Vector2D startPosition, Vector2D endPosition, Vector2D scale) : renderer(renderer),enemyManager(enemyManager), effectsManager(effectsManager), sprite(sprite), position(startPosition), endPosition(endPosition), scale(scale)
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

void BulletBase::Update()
{
	if (isMoving == true)
	{
		SetPosition(Vector2D::Lerp(startPosition, endPosition, delta));
		if (delta <= 1.0f)
		{
			delta += 0.0065f;
		}
		else
		{
			isMoving = false;
			EffectBase* explosion = new EffectBase(renderer,enemyManager, sprite, position,Vector2D::Zero(), Vector2D::One() * (GameManager::DEFAULT_SPRITE_SIZE * 2.0f));
			effectsManager->AddEffect(explosion);
		}
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

