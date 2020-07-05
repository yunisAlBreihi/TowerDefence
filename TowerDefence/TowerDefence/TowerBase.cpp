#include "TowerBase.h"

TowerBase::TowerBase()
{
}

TowerBase::TowerBase(SDL_Renderer* renderer, Sprite* sprite, Vector2D position, Vector2D scale) : renderer(renderer), sprite(sprite), position(position), scale(scale)
{
	dstRect = { this->position.x, this->position.y, this->scale.x, this->scale.y };
}

TowerBase::~TowerBase()
{
}

void TowerBase::Start()
{
}

void TowerBase::Update()
{
}

void TowerBase::Render()
{
	SDL_RenderCopy(renderer, sprite->GetTexture(), nullptr, &dstRect);
}

void TowerBase::Destroy()
{
}

void TowerBase::SetPosition(Vector2D vector2D)
{
	position = vector2D;
	dstRect.x = position.x;
	dstRect.y = position.y;
}
