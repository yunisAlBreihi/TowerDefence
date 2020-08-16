#pragma once
#include <SDL.h>
#include "IRenderable.h"
#include "EnemyManager.h"
#include "EffectsManager.h"
#include "Sprite.h"
#include "Vector2D.h"
#include "Enums.h"

class BulletBase : public IRenderable
{
private:

protected:
	SDL_Renderer* renderer = nullptr;
	EnemyManager* enemyManager = nullptr;
	EffectsManager* effectsManager = nullptr;
	BulletType bulletType;
	Sprite* sprite = nullptr;
	float speed = 3.0f;
	Vector2D position = { 0,0 };
	Vector2D startPosition = { 0,0 };
	Vector2D endPosition = { 0,0 };
	Vector2D scale = { 0,0 };
	SDL_Rect dstRect = { 0,0,0,0 };
	float movementDelta = 0.0f;
	bool isMoving = false;

public:

private:

public:
	BulletBase();
	BulletBase(SDL_Renderer* renderer,EnemyManager* enemyManager,EffectsManager* effectsManager,BulletType bulletType, Sprite* sprite, Vector2D startPosition, Vector2D endPosition, Vector2D scale);
	~BulletBase();

	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Destroy() override;

	void SetPosition(Vector2D vector2D);
	Vector2D GetPosition() { return Vector2D(dstRect.x, dstRect.y); }
	Sprite* GetSprite() { return sprite; }
	SDL_Rect GetDstRect() { return dstRect; }
	void StartMoving(Vector2D startPosition, Vector2D endPosition);
};

