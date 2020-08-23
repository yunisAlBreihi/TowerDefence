#include "ScreenImageUI.h"

#pragma region Construction
ScreenImageUI::ScreenImageUI(Managers* managers, Sprite* sprite, Vector2D position, Vector2D scale)
{
	this->managers = managers;
	this->sprite = sprite;
	this->position = position;
	this->scale = scale;

	this->dstRect = { (int)this->position.x, (int)this->position.y, (int)this->scale.x, (int)this->scale.y };
	this->isActive = true;
}

ScreenImageUI::~ScreenImageUI()
{
}
#pragma endregion Construction