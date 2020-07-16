#pragma once
#include <SDL.h>
#include "IRenderable.h"
#include "Vector2D.h"
#include "Sprite.h"
#include "Dijkstra.h"
#include "Tile.h"

class EnemyBase : public IRenderable
{
private:

protected:
	SDL_Renderer* renderer = nullptr;
	std::vector<Tile*> path;
	int pathIndex = 0;
	Sprite* sprite = nullptr;
	Vector2D position = { 0,0 };
	Vector2D scale = { 0,0 };
	Vector2D currentStartPosition = { 0,0 };
	SDL_Rect dstRect = { 0,0,0,0 };
	float delta = 0;
	bool hasReachedEnd = false;

	float health = 3.0f;

	//For when the enemy is frozen
	float speed = 1.0f;
	float originalSpeed = 1.0f;
	float frozenSpeed = 0.5f;
	float freezeTimer = 0.0f;
	float maxFreezeTime = 2.0f;
	bool isFrozen = false;

public:

private:

	void MoveToEnd();
	void FreezeTimer();

public:

	EnemyBase();
	EnemyBase(SDL_Renderer* renderer, std::vector<Tile*> path, Sprite* sprite, Vector2D position, Vector2D scale);
	virtual ~EnemyBase() = 0;

	void Start();
	void Update();
	void Render();
	void Destroy();

	void TakeDamage(float damage);
	bool IsDead();

	//For when the enemy is frozen
	void Freeze(float freezeTime, float freezeSpeed);
	bool IsFrozen();

	void SetPosition(Vector2D vector2D);
	Vector2D GetPosition() { return Vector2D(dstRect.x, dstRect.y); }
	void SetSpeed(float speed);
	float GetSpeed() { return speed; }
	Sprite* GetSprite() { return sprite; }
	SDL_Rect GetDstRect() { return dstRect; }
	bool HasReachedEnd() { return hasReachedEnd; }
};