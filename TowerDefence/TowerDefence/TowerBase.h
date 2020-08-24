#pragma once
#include <SDL.h>
#include "IRenderable.h"
#include "Sprite.h"
#include "Managers.h"
#include "EnemyManager.h"
#include "BulletManager.h"
#include "EffectManager.h"
#include "SpriteManager.h"
#include "Collider.h"
#include "Enums.h"

class TowerBase : public IRenderable
{
protected:
	Managers* managers = nullptr;
	EnemyManager* enemyManager = nullptr;
	SpriteManager* spriteManager = nullptr;
	BulletManager* bulletManager = nullptr;
	EffectManager* effectsManager = nullptr;

	//Attributes
	BulletType bulletType = BulletType::Regular;
	Sprite* sprite = nullptr;
	Vector2D position = { 0,0 };
	Vector2D scale = { 0,0 };
	Vector2D circlePosition = { 0,0 };
	SDL_Rect dstRect = { 0,0,0,0 };

	//For Collider
	Collider* collider = nullptr;
	float collisionRadius = 80.0f;
	//Sets the interval that the circle is drawn in steps. the higher number, the less it draws.
	int debugCircleQuality = 4;

	//For shooting
	Enemy* currentEnemyTarget = nullptr;
	float shootTimer = 0.0f;
	float shootMaxTime = 0.0f;

public:
	TowerBase();
	TowerBase(Managers* managers, BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D scale);
	~TowerBase();

	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;

	void Reset(Managers* managers, BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D scale);
	void Disable();

	void SetEnemyTarget();
	void Shoot(float deltaTime);
	virtual void OnShoot() = 0;

	void SetPosition(Vector2D vector2D);
	void DrawDebugRange();

	Vector2D GetPosition() { return Vector2D(dstRect.x, dstRect.y); }
	BulletType GetType() { return bulletType; }
	Sprite* GetSprite() { return sprite; }
	SDL_Rect GetDstRect() { return dstRect; }
};