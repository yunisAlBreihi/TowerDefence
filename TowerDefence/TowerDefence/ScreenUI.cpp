#include "ScreenUI.h"

ScreenUI::ScreenUI(Managers* managers, Sprite* sprite, Vector2D position, Vector2D scale)
{
	this->managers = managers;
	this->sprite = sprite;
	this->position = position;
	this->scale = scale;

	this->dstRect = { (int)this->position.x, (int)this->position.y, (int)this->scale.x, (int)this->scale.y };
}