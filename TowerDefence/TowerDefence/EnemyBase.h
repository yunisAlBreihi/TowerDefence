#pragma once
#include <SDL.h>
#include "IRenderable.h"
#include "Managers.h"
#include "Vector2D.h"
#include "Sprite.h"
#include "Dijkstra.h"
#include "Tile.h"

class EnemyBase : public IRenderable
{
private:

protected:
	Managers* managers = nullptr;
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
	float speed = 2.0f;
	float originalSpeed = 0.0f;
	float frozenSpeed = 0.5f;
	float freezeTimer = 0.0f;
	float maxFreezeTime = 2.0f;
	bool isFrozen = false;
	bool hasCountedDeath = false;

public:

private:

	void MoveToEnd(float deltaTime);
	void FreezeTimer(float deltaTime);

public:

	EnemyBase();
	EnemyBase(Managers* managers, std::vector<Tile*> path, Sprite* sprite, Vector2D position, Vector2D scale);
	virtual ~EnemyBase() = 0;

	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Destroy() override;

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