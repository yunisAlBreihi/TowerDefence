#include "ScreenUI.h"

ScreenUI::ScreenUI(Managers* managers, Sprite* sprite, Vector2D position, Vector2D scale)
{
	this->managers = managers;
	this->sprite = sprite;
	this->position = position;
	this->scale = scale;

	this->dstRect = { this->position.x, this->position.y, this->scale.x, this->scale.y };
}