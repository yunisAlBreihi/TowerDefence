#pragma once
#include <SDL.h>
#include <iostream>
#include "IRenderedObject.h"
#include "Vecto2D.h"

class Sprite : IRenderedObject
{
private:

protected:

	std::string filePath = "";
	std::string name = "";

	Vector2D position = { 0,0 };
	int width = 0;
	int height = 0;

	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Rect dstRect = {0,0,0,0};
	SDL_Renderer* renderer = nullptr;

public:

private:

protected:

	std::string SetFileName();
	virtual void NotUsed() = 0;

public:

	Sprite();
	~Sprite();
	
	void Start();
	void Start(SDL_Renderer* renderer, std::string filePath, int width, int height);
	void Update();
	void Render();
	void Destroy();

	void SetPosition(Vector2D vector2D);
	Vector2D GetPosition();
};

