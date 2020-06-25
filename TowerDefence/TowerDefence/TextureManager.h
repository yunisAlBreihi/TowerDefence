#pragma once
#include <vector>
#include <SDL.h>

class TextureManager
{
private:
	std::vector<SDL_Texture*> textureList;
};