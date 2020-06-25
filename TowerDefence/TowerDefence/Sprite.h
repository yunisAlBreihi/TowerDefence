#pragma once
#include <SDL.h>
#include <iostream>
#include "Vecto2D.h"

enum class SpriteName
{
	daker,
};

class Sprite
{
private:

protected:

	SpriteName name;
	std::string filePath;

	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Renderer* renderer = nullptr;

public:

private:

public:

	Sprite(SDL_Renderer* renderer, SpriteName spriteName);
	~Sprite();

	SDL_Texture* Texture() { return texture; };
	SpriteName GetSpriteName() { return name; };
};

