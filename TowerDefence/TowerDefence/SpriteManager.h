#pragma once
#include <vector>
#include "Sprite.h"

class SpriteManager
{
private:

	std::vector<Sprite*> sprites;

public:

private:

public:

	void AddSprite(Sprite* sprite);
	Sprite* GetSprite(SpriteName spriteName);
};