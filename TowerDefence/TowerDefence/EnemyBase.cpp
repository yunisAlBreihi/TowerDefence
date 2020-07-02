#include "EnemyBase.h"

EnemyBase::EnemyBase(SDL_Renderer* renderer, Sprite* sprite, Vector2D position, Vector2D scale) : renderer(renderer), sprite(sprite), position(position), scale(scale)
{
	dstRect = { this->position.x, this->position.y, this->scale.x, this->scale.y };
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Start()
{
}

void EnemyBase::Update()
{

}

void EnemyBase::Render()
{
	SDL_RenderCopy(renderer, sprite->GetTexture(), nullptr, &dstRect);
}

void EnemyBase::Destroy()
{
}

void EnemyBase::SetPosition(Vector2D vector2D)
{
	position = vector2D;
	dstRect.x = position.x;
	dstRect.y = position.y;
}