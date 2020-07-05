#include "SpriteManager.h"

void SpriteManager::AddSprite(Sprite* sprite)
{
	sprites.push_back(sprite);
}

Sprite* SpriteManager::GetSprite(SpriteName spriteName)
{

	for (Sprite* sprite : sprites)
	{
		if (sprite->GetSpriteName() == spriteName)
		{
			return sprite;
		}
	}

	std::cout << "Could not find the sprite you specified in the spriteManager" << std::endl;
	return nullptr;
}