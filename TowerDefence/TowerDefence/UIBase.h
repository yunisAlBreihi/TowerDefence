#pragma once
#include <SDL.h>
#include "IRenderable.h"
#include "Managers.h"
#include "Vector2D.h"
#include "Sprite.h"

class UIBase : public IRenderable
{
protected:
	Managers* managers = nullptr;

	//Attributes
	Sprite* sprite = nullptr;
	Vector2D position = { 0,0 };
	Vector2D scale = { 0,0 };
	SDL_Rect dstRect = { 0,0,0,0 };

public:
	UIBase();
	UIBase(Sprite* sprite, Vector2D position, Vector2D scale);
	virtual ~UIBase() = 0;

	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;

	void Disable();
	void Reset(Sprite* sprite, Vector2D position, Vector2D scale);

	void SetPosition(Vector2D position);
	void SetScale(Vector2D scale);
	Sprite* GetSprite() { return sprite; }
};