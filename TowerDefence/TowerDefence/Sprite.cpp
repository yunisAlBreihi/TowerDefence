#include "Sprite.h"
#include <SDL_image.h>

#pragma region Construction
Sprite::Sprite(SDL_Renderer* renderer, SpriteName spriteName, std::string filePath) : renderer(renderer), name(spriteName), filePath(filePath)
{
	surface = IMG_Load(filePath.c_str());
	texture = SDL_CreateTextureFromSurface(this->renderer, surface);
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}
#pragma endregion Construction