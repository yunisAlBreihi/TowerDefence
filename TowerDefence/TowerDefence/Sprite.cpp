#include "Sprite.h"
#include <SDL_image.h>

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
}

void Sprite::Start()
{
}

void Sprite::Start(SDL_Renderer* renderer, std::string filePath, int width, int height)
{
	this->renderer = renderer;
	this->filePath = filePath;
	this->width = width;
	this->height = height;

	name = SetFileName();
	dstRect = { position.x,position.y,this->width, this->height };
	surface = IMG_Load(filePath.c_str());
	texture = SDL_CreateTextureFromSurface(this->renderer, surface);
}

void Sprite::Update()
{
}

void Sprite::Render()
{
	SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
}

void Sprite::Destroy()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
	surface = nullptr;
	renderer = nullptr;
}



std::string Sprite::SetFileName()
{
	char seperator = '/';

	//If on a win32 system, change the seperator to match that system.
#ifdef _WIN32
	seperator = '\\';
#endif // _WIN32

	size_t i = filePath.rfind(seperator, filePath.length());
	if (i != std::string::npos)
	{
		return(filePath.substr(i + 1, filePath.length() - i));
	}
	return ("");
}

void Sprite::SetPosition(Vector2D vector2D)
{
	position = vector2D;
	dstRect.x = position.x;
	dstRect.y = position.y;
}

Vector2D Sprite::GetPosition()
{
	return Vector2D(dstRect.x, dstRect.y);
}