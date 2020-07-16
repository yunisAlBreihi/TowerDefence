#pragma once
#include <SDL.h>
#include "IRenderable.h"
#include "Sprite.h"
#include "Vector2D.h"

class EffectBase : public IRenderable
{
private:
	SDL_Renderer* renderer = nullptr;
	Sprite* sprite = nullptr;
	Vector2D position = { 0,0 };
	Vector2D startPosition = { 0,0 };
	Vector2D endPosition = { 0,0 };
	Vector2D scale = { 0,0 };
	Vector2D startScale = { 0,0 };
	Vector2D endScale = { 0.0f, 0.0f };
	SDL_Rect dstRect = { 0,0,0,0 };
	float delta = 0.0f;

public:

private:

public:
	EffectBase(SDL_Renderer* renderer, Sprite* sprite, Vector2D position, Vector2D startScale, Vector2D endScale);

	void Start();
	void Update();
	void Render();
	void Destroy();

	void SetPosition(Vector2D position);
	void SetScale(Vector2D scale);
	Sprite* GetSprite() { return sprite; }
	Vector2D GetPosition() { return position; }
	Vector2D GetScale() { return scale; }

	void Expand();
};