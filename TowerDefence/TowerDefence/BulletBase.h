#pragma once
#include <memory>
#include <SDL.h>
#include "IRenderable.h"
#include "Managers.h"
#include "EnemyManager.h"
#include "EffectManager.h"
#include "Sprite.h"
#include "Vector2D.h"
#include "Enums.h"

class BulletBase : public IRenderable
{
protected:
	Managers* managers = nullptr;
	SDL_Renderer* renderer = nullptr;

	//Attributes
	Sprite* sprite = nullptr;
	BulletType bulletType = BulletType::Regular;
	float speed = 8.0f;
	Vector2D position = { 0,0 };
	Vector2D startPosition = { 0,0 };
	Vector2D endPosition = { 0,0 };
	Vector2D scale = { 0,0 };
	SDL_Rect dstRect = { 0,0,0,0 };

	float movementDelta = 0.0f;
protected:
	BulletBase();

	void Clear();
	void OnMove(float deltaTime);

public:
	BulletBase(BulletType bulletType, Sprite* sprite, Vector2D startPosition, Vector2D endPosition, Vector2D scale);
	~BulletBase();

	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Destroy() override;
	void Reset(BulletType bulletType, Sprite* sprite, Vector2D startPosition, Vector2D endPosition, Vector2D scale);

	void SetPosition(Vector2D vector2D);
	Vector2D GetPosition() { return Vector2D(dstRect.x, dstRect.y); }
	Sprite* GetSprite() { return sprite; }
	SDL_Rect GetDstRect() { return dstRect; }
	BulletType GetType() { return bulletType; }

	virtual void OnReachedDestination() = 0;
};