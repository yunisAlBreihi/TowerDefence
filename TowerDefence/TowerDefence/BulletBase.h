#pragma once
#include <SDL.h>
#include "IRenderable.h"
#include "Sprite.h"
#include "Vector2D.h"

class BulletBase : public IRenderable
{
private:

protected:
	SDL_Renderer* renderer = nullptr;
	Sprite* sprite = nullptr;
	Vector2D position = { 0,0 };
	Vector2D startPosition = { 0,0 };
	Vector2D endPosition = { 0,0 };
	Vector2D scale = { 0,0 };
	SDL_Rect dstRect = { 0,0,0,0 };
	float delta = 0.0f;
	bool isMoving = false;

public:

private:

public:
	//BulletBase();
	BulletBase(SDL_Renderer* renderer, Sprite* sprite, Vector2D startPosition, Vector2D endPosition, Vector2D scale);
	~BulletBase();

	void Start();
	void Update();
	void Render();
	void Destroy();

	void SetPosition(Vector2D vector2D);
	Vector2D GetPosition() { return Vector2D(dstRect.x, dstRect.y); }
	Sprite* GetSprite() { return sprite; }
	SDL_Rect GetDstRect() { return dstRect; }
	void StartMoving(Vector2D startPosition, Vector2D endPosition);
};

