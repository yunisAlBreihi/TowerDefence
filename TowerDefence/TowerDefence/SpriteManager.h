#pragma once
#include <vector>
#include "ManagerBase.h"
#include "Sprite.h"

class SpriteManager : public ManagerBase
{
private:

	std::vector<Sprite*> sprites;

public:

private:

public:
	SpriteManager();
	~SpriteManager();

	void AddSprite(Sprite* sprite);
	Sprite* GetSprite(SpriteName spriteName);
};