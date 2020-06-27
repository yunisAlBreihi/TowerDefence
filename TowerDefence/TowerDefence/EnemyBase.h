#pragma once
#include <SDL.h>
#include "IRenderable.h"
#include "Vecto2D.h"
#include "Sprite.h"

class EnemyBase : public IRenderable
{
private:
	SDL_Renderer* renderer = nullptr;
	Sprite* sprite = nullptr;
	Vector2D position = { 0,0 };
	Vector2D scale = { 0,0 };
	SDL_Rect dstRect = { 0,0,0,0 };

public:

private:

public:

	EnemyBase(SDL_Renderer* renderer, Sprite* sprite, Vector2D position, Vector2D scale);
	~EnemyBase();

	void Start();
	void Update();
	void Render();
	void Destroy();

	void SetPosition(Vector2D vector2D);
	Vector2D GetPosition();
};