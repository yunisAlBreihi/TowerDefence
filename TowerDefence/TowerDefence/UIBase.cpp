#include "UIBase.h"

UIBase::UIBase(SDL_Renderer* renderer, Sprite* sprite, Vector2D position, Vector2D scale) : renderer(renderer), sprite(sprite), position(position), scale(scale)
{
	dstRect = { this->position.x, this->position.y, this->scale.x, this->scale.y };
}

UIBase::~UIBase()
{
}

void UIBase::Start()
{

}

void UIBase::Update(float deltaTime)
{
}

void UIBase::Render()
{
	//TODO: add a isActive bool for rendering UI or not
	SDL_RenderCopy(renderer, sprite->GetTexture(), nullptr, &dstRect);
}

void UIBase::Destroy()
{
	renderer = nullptr;
}

void UIBase::SetPosition(Vector2D position)
{
	this->position = position;
	dstRect.x = this->position.x;
	dstRect.y = this->position.y;
}

void UIBase::SetScale(Vector2D scale)
{
	this->scale = scale;
	dstRect.w = this->scale.x;
	dstRect.h = this->scale.y;
}