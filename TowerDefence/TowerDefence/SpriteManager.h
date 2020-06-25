#pragma once
#include <vector>
#include "Sprite.h"

class SpriteManager
{
private:

	std::vector<Sprite*> spriteList;

public:

private:

public:

	void AddSprite(Sprite* sprite);
	Sprite* GetSprite(SpriteName spriteName);
};