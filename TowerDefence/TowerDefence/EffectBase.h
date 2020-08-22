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

class EffectBase : public IRenderable
{
private:
protected:

	Managers* managers = nullptr;
	EnemyManager* enemyManager = nullptr;
	std::vector<Enemy*> enemiesHit;
	BulletType bulletType = BulletType::Regular;
	Sprite* sprite = nullptr;
	Collider* collider = nullptr;
	Vector2D position = { 0,0 };
	Vector2D startPosition = { 0,0 };
	Vector2D endPosition = { 0,0 };
	Vector2D scale = { 0,0 };
	Vector2D startScale = { 0,0 };
	Vector2D endScale = { 0.0f, 0.0f };
	Vector2D colliderPosition = { 0.0f, 0.0f };
	SDL_Rect dstRect = { 0,0,0,0 };
	float damage = 0.75f;
	float freezeTime = 3.0f;
	float freezeSpeed = 0.75f;
	float delta = 0.0f;
	float expandSpeed = 6.0f;
	bool reachedMaxSize = false;
public:

private:
	void Expand(float deltaTime);
protected:

public:
	EffectBase();
	EffectBase(Managers* managers, BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D startScale, Vector2D endScale);
	virtual ~EffectBase() = 0;

	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Destroy() override;

	virtual void OnHit(Enemy* enemy) = 0;
	void LerpExplosionScale(float deltaTime);

	void SetPosition(Vector2D position);
	void SetScale(Vector2D scale);
	Sprite* GetSprite() { return sprite; }
	Vector2D GetPosition() { return position; }
	Vector2D GetScale() { return scale; }
	BulletType GetType() { return bulletType; }

	void Reset(Managers* managers, BulletType bulletType, Sprite* sprite, Vector2D position, Vector2D startScale, Vector2D endScale);
	void Clear();

};