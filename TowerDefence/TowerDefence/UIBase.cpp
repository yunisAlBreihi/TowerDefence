#include "UIBase.h"

#pragma region Construction
UIBase::UIBase()
{
}

UIBase::UIBase(Sprite* sprite, Vector2D position, Vector2D scale) : sprite(sprite), position(position), scale(scale)
{
	managers = Managers::GetInstance();
	dstRect = { (int)this->position.x, (int)this->position.y, (int)this->scale.x, (int)this->scale.y };
	isActive = true;
}

UIBase::~UIBase()
{
}
#pragma endregion Construction

#pragma region GameLoop
void UIBase::Start()
{
}

void UIBase::Update(float deltaTime)
{
}

void UIBase::Render()
{
	if (isActive == true)
	{
		SDL_RenderCopy(managers->GetRenderer(), sprite->GetTexture(), nullptr, &dstRect);
	}
}
#pragma endregion GameLoop

#pragma region Disable
void UIBase::Disable()
{
	position = Vector2D::Zero();
	scale = Vector2D::Zero();
	isActive = false;
}

void UIBase::Reset(Sprite* sprite, Vector2D position, Vector2D scale)
{
	managers = Managers::GetInstance();
	dstRect = { (int)this->position.x, (int)this->position.y, (int)this->scale.x, (int)this->scale.y };
	this->sprite = sprite;
	this->position = position;
	this->scale = scale;
	isActive = true;
}
#pragma endregion Disable

#pragma region Set
void UIBase::SetPosition(Vector2D position)
{
	//Round the values, since SDL_Rect values is in int, otherwise get Stutter
	this->position = Vector2D(round(position.x),round(position.y));
	dstRect.x = (int)this->position.x;
	dstRect.y = (int)this->position.y;
}

void UIBase::SetScale(Vector2D scale)
{
	//Round the values, since SDL_Rect values is in int, otherwise get Stutter
	this->scale = Vector2D(round(scale.x), round(scale.y));
	dstRect.w = (int)this->scale.x;
	dstRect.h = (int)this->scale.y;
}
#pragma endregion Set