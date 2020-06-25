#include "Sprite.h"
#include <SDL_image.h>

Sprite::Sprite(SDL_Renderer* renderer, SpriteName spriteName)
{
	this->renderer = renderer;
	switch (spriteName)
	{
	case SpriteName::daker:
		filePath = "Sprites/daker.jpg";
		break;
	default:
		break;
	}
	surface = IMG_Load(filePath.c_str());
	texture = SDL_CreateTextureFromSurface(this->renderer, surface);
}

Sprite::~Sprite()
{

}
