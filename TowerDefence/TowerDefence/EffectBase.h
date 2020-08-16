#pragma once
#include <SDL.h>
#include "IRenderable.h"
#include "EnemyManager.h"
#include "Sprite.h"
#include "Vector2D.h"
#include "Collider.h"
#include "EnemyBase.h"
#include "Enums.h"

class EffectBase : public IRenderable
{
private:
	SDL_Renderer* renderer = nullptr;
	EnemyManager* enemyManager = nullptr;
	BulletType bulletType;
	Sprite* sprite = nullptr;
	Collider* collider = nullptr;
	Vector2D position = { 0,0 };
	Vector2D startPosition = { 0,0 };
	Vector2D endPosition = { 0,0 };
	Vector2D scale = { 0,0 };
	Vector2D startScale = { 0,0 };
	Vector2D endScale = { 0.0f, 0.0f };
	SDL_Rect dstRect = { 0,0,0,0 };
	float delta = 0.0f;
	float startRadius = 0.0f;
	float endRadius = 0.0f;
	float expandSpeed = 4.0f;
	bool reachedMaxSize = false;

	EnemyBase* currentTarget = nullptr;

	std::vector<EnemyBase*> enemiesHit;

public:

private:

public:
	EffectBase(SDL_Renderer* renderer,EnemyManager* enemyManager, BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D startScale, Vector2D endScale);

	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Destroy() override;

	void SetPosition(Vector2D position);
	void SetScale(Vector2D scale);
	Sprite* GetSprite() { return sprite; }
	Vector2D GetPosition() { return position; }
	Vector2D GetScale() { return scale; }

	void LerpExplosionScale(float deltaTime);
};