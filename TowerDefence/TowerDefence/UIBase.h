#pragma once
#include <SDL.h>
#include "IRenderable.h"
#include "Vector2D.h"
#include "Sprite.h"

class UIBase : public IRenderable
{
private:
	SDL_Renderer* renderer = nullptr;
	Sprite* sprite = nullptr;
	Vector2D position = { 0,0 };
	Vector2D scale = { 0,0 };
	SDL_Rect dstRect = { 0,0,0,0 };

public:
private:
	//virtual ~UIBase() = 0;
public:
	UIBase(SDL_Renderer* renderer, Sprite* sprite, Vector2D position, Vector2D scale);
	~UIBase();

	void Start() override;
	void Update() override;
	void Render() override;
	void Destroy() override;

	void SetPosition(Vector2D position);
	void SetScale(Vector2D scale);

	Sprite* GetSprite() { return sprite; }
};