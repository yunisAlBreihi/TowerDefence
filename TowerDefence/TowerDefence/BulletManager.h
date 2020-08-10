#pragma once
#include <vector>
#include "ManagerBase.h"
#include "BulletBase.h"

class BulletManager : public IRenderable , public ManagerBase
{
private:
	EffectsManager* effectsManager = nullptr;
	std::vector<Sprite*> sprites;
	std::vector<BulletBase*> bullets;
	SDL_Renderer* renderer = nullptr;

public:

private:
	BulletBase* CreateBullet(Sprite* bulletSprite, Vector2D position, Vector2D scale);

public:
	BulletManager(SDL_Renderer* renderer);

	void Start();
	void Update();
	void Render();
	void Destroy();

	void AddBullet(BulletBase* bullet);
};