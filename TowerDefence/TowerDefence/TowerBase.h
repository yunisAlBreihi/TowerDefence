#pragma once
#include <SDL.h>
#include "IRenderable.h"
#include "Sprite.h"
#include "EnemyManager.h"
#include "BulletManager.h"

class TowerBase : public IRenderable
{
private:
protected:
	SDL_Renderer* renderer = nullptr;
	EnemyManager* enemyManager = nullptr;
	SpriteManager* spriteManager = nullptr;
	BulletManager* bulletManager = nullptr;
	EnemyBase* currentEnemyTarget = nullptr;
	Sprite* sprite = nullptr;
	Vector2D position = { 0,0 };
	Vector2D scale = { 0,0 };
	Vector2D circlePosition = { 0,0 };
	SDL_Rect dstRect = { 0,0,0,0 };
	float collisionRadius = 80.0f;

	float shootTimer = 0.0f;
	float shootMaxTime = 750.0f;

public:

private:

public:
	TowerBase();
	TowerBase(SDL_Renderer* renderer, EnemyManager* enemeyManager,SpriteManager* spriteManager, BulletManager* bulletManager, Sprite* sprite, Vector2D position, Vector2D scale);
	virtual ~TowerBase() = 0;

	void Start();
	void Update();
	void Render();
	void Destroy();

	bool isPointInCircle(Vector2D firstPosition, Vector2D secondPosition, float radius);
	void DrawDebugCircle();

	void SetPosition(Vector2D vector2D);

	Vector2D GetPosition() { return Vector2D(dstRect.x, dstRect.y); }
	Sprite* GetSprite() { return sprite; }
	SDL_Rect GetDstRect() { return dstRect; }
};