#include "EffectBase.h"
#include "GameManager.h"

EffectBase::EffectBase(SDL_Renderer* renderer, Sprite* sprite, Vector2D position, Vector2D startScale, Vector2D endScale) : renderer(renderer), sprite(sprite), position(position), startScale(startScale), endScale(endScale)
{
	startPosition = position;
	endPosition = startPosition - (endScale * 0.5f);
	scale = startScale;
	dstRect = { this->startPosition.x, this->startPosition.y, this->scale.x, this->scale.y };
	startScale = this->scale;
}

void EffectBase::Start()
{
}

void EffectBase::Update()
{
	Expand();
}

void EffectBase::Render()
{
	SDL_RenderCopy(renderer, sprite->GetTexture(), nullptr, &dstRect);
}

void EffectBase::Destroy()
{
}

void EffectBase::SetPosition(Vector2D position)
{
	this->position = position;
	dstRect.x = this->position.x;
	dstRect.y = this->position.y;
}

void EffectBase::SetScale(Vector2D scale)
{
	this->scale = scale;
	dstRect.w = this->scale.x;
	dstRect.h = this->scale.y;
}

void EffectBase::Expand()
{
	SetScale(Vector2D::Lerp(startScale, endScale, delta));
	SetPosition(Vector2D::Lerp(startPosition, endPosition, delta));

	if (delta <= 1.0f)
	{
		delta += 0.003f;
	}
}
