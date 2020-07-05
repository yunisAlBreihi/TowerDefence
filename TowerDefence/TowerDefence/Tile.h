#pragma once
#include <string>
#include <SDL.h>
#include "Sprite.h"
#include "IRenderable.h"

class Tile : public IRenderable
{
private:

	SDL_Renderer* renderer = nullptr;
	Sprite* sprite = nullptr;
	Vector2D position = { 0,0 };
	Vector2D scale = { 0,0 };
	SDL_Rect dstRect = { 0,0,0,0 };
	bool isWalkable = false;

public:

private:

public:
	Tile() {}
	Tile(SDL_Renderer* renderer, Sprite* sprite, Vector2D position, Vector2D scale, bool isWalkable);
	void Start();
	void Update();
	void Render();
	void Destroy();

	void SetPosition(Vector2D position);
	void SetScale(Vector2D scale);
	
	Vector2D GetPosition() { return position; }
	Vector2D GetScale() { return scale; }
	Sprite* GetSprite() { return sprite; }
	bool IsWalkable() { return isWalkable; }
};