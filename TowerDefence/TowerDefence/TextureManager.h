#pragma once
#include <vector>
#include <SDL.h>
#include "ManagerBase.h"

class TextureManager : public ManagerBase
{
private:
	std::vector<SDL_Texture*> textures;
public:
private:
public:
	TextureManager();
	~TextureManager();
};