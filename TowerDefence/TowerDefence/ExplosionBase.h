#pragma once
#include <SDL.h>
#include "IRenderable.h"
#include "Managers.h"
#include "EnemyManager.h"
#include "Sprite.h"
#include "Vector2D.h"
#include "Collider.h"
#include "Enemy.h"
#include "Enums.h"

class ExplosionBase : public IRenderable
{
protected:
	Managers* managers = nullptr;
	EnemyManager* enemyManager = nullptr;
	std::vector<Enemy*> enemiesHit;
	Collider* collider = nullptr;

	//Attributes
	Sprite* sprite = nullptr;
	BulletType bulletType = BulletType::Regular;
	Vector2D position = { 0,0 };
	Vector2D startPosition = { 0,0 };
	Vector2D endPosition = { 0,0 };
	Vector2D scale = { 0,0 };
	Vector2D startScale = { 0,0 };
	Vector2D endScale = { 0.0f, 0.0f };
	Vector2D colliderPosition = { 0.0f, 0.0f };
	SDL_Rect dstRect = { 0,0,0,0 };
	float damage = 0.75f;

	//Variables for expansion
	float expansionDelta = 0.0f;
	float expandSpeed = 6.0f;
	bool reachedMaxSize = false;

private:
	void Disable();

	void Expand(float deltaTime);
	void LerpExplosionScale(float deltaTime);

public:
	ExplosionBase();
	ExplosionBase(BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D startScale, Vector2D endScale);
	virtual ~ExplosionBase() = 0;

	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;

	void Reset(BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D startScale, Vector2D endScale);

	void SetPosition(Vector2D position);
	void SetScale(Vector2D scale);
	Sprite* GetSprite() { return sprite; }
	Vector2D GetPosition() { return position; }
	Vector2D GetScale() { return scale; }
	BulletType GetType() { return bulletType; }

	virtual void OnHit(Enemy* enemy) = 0;
};