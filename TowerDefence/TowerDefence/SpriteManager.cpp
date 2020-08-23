#include "SpriteManager.h"

#pragma region Construction
SpriteManager::SpriteManager()
{
	name = ManagerName::SpriteManager;
}

SpriteManager::~SpriteManager()
{
}
#pragma endregion Construction

#pragma region ManageSprites
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
#pragma endregion ManageSprites