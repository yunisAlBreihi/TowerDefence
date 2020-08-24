#pragma once
#include <vector>
#include "ManagerBase.h"
#include "Sprite.h"

class SpriteManager : public ManagerBase
{
private:
	std::vector<Sprite*> sprites;

public:
	SpriteManager();

	void AddSprite(Sprite* sprite);
	Sprite* GetSprite(SpriteName spriteName);
};