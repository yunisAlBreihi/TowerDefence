#include "Sprite.h"
#include <SDL_image.h>

Sprite::Sprite(SDL_Renderer* renderer, SpriteName spriteName)
{
	this->renderer = renderer;
	name = spriteName;
	switch (spriteName)
	{
	case SpriteName::grass:
		filePath = "Sprites/grass.jpg";
		isWalkable = true;
		break;
	case SpriteName::water:
		filePath = "Sprites/water.jpg";
		isWalkable = false;
		break;
	case SpriteName::tower01:
		filePath = "Sprites/tower01.jpg";
		isWalkable = false;
		break;
	case SpriteName::tower02:
		filePath = "Sprites/tower02.jpg";
		isWalkable = false;
		break;
	case SpriteName::startPosition:
		filePath = "Sprites/startPosition.jpg";
		isWalkable = true;
		break;
	case SpriteName::endPosition:
		filePath = "Sprites/endPosition.jpg";
		isWalkable = true;
		break;
	default:
		filePath = "Sprites/missing.jpg";
		isWalkable = false;
		break;
	}
	surface = IMG_Load(filePath.c_str());
	texture = SDL_CreateTextureFromSurface(this->renderer, surface);
}

Sprite::~Sprite()
{

}
