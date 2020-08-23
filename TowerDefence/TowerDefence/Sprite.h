#pragma once
#include <SDL.h>
#include <iostream>
#include "Vector2D.h"
#include "Enums.h"

class Sprite
{
protected:
	//SDL
	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Renderer* renderer = nullptr;

	//Attributes
	SpriteName name;
	std::string filePath;

public:
	Sprite(SDL_Renderer* renderer, SpriteName spriteName, std::string filePath);
	~Sprite();

	SDL_Texture* GetTexture() { return texture; };
	SpriteName GetSpriteName() { return name; };
};

