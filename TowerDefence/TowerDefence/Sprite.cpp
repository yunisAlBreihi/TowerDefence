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
		break;
	case SpriteName::water:
		filePath = "Sprites/water.jpg";
		break;
	case SpriteName::tower01:
		filePath = "Sprites/tower01.jpg";
		break;
	case SpriteName::tower02:
		filePath = "Sprites/tower02.jpg";
		break;
	case SpriteName::startPosition:
		filePath = "Sprites/startPosition.jpg";
		break;
	case SpriteName::endPosition:
		filePath = "Sprites/endPosition.jpg";
		break;
	default:
		filePath = "Sprites/missing.jpg";
		break;
	}
	surface = IMG_Load(filePath.c_str());
	texture = SDL_CreateTextureFromSurface(this->renderer, surface);
}

Sprite::~Sprite()
{

}
