#pragma once
#include <SDL.h>
#include "IRenderable.h"
#include "Sprite.h"
#include "Managers.h"
#include "EnemyManager.h"
#include "BulletManager.h"
#include "EffectsManager.h"
#include "SpriteManager.h"
#include "Collider.h"
#include "Enums.h"

class TowerBase : public IRenderable
{
private:
protected:
	Managers* managers = nullptr;
	EnemyManager* enemyManager = nullptr;
	SpriteManager* spriteManager = nullptr;
	BulletManager* bulletManager = nullptr;
	EffectsManager* effectsManager = nullptr;
	EnemyBase* currentEnemyTarget = nullptr;
	Collider* collider = nullptr;
	Sprite* sprite = nullptr;
	Vector2D position = { 0,0 };
	Vector2D scale = { 0,0 };
	Vector2D circlePosition = { 0,0 };
	SDL_Rect dstRect = { 0,0,0,0 };

	float collisionRadius = 80.0f;
	//Sets the interval that the circle is drawn in steps. the higher number, the less it draws.
	int debugCircleQuality = 4;

	float shootTimer = 0.0f;
	float shootMaxTime = 0.75f;

public:

private:

public:
	TowerBase();
	TowerBase(Managers* managers, Sprite* sprite, Vector2D position, Vector2D scale);
	virtual ~TowerBase() = 0;

	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Destroy() override;

	void SetEnemyTarget();
	void Shoot(float deltaTime);
	virtual void OnShoot() = 0;

	void SetPosition(Vector2D vector2D);
	void DrawDebugCircle();

	Vector2D GetPosition() { return Vector2D(dstRect.x, dstRect.y); }
	Sprite* GetSprite() { return sprite; }
	SDL_Rect GetDstRect() { return dstRect; }
};