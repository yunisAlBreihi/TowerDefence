#pragma once
#include <SDL.h>
#include <iostream>
#include "Vector2D.h"

enum class SpriteName
{
	grass = 0,
	water = 1,
	tower01 = 2,
	tower02 = 3,
	startPosition = 8,
	endPosition = 9,
	EnemySmall = 20,
	EnemyBig = 21,
	TowerSmall = 30,
	TowerBig = 31,
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

	SDL_Texture* GetTexture() { return texture; };
	SpriteName GetSpriteName() { return name; };
};

