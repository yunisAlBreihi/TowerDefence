#pragma once
#include <vector>
#include "BulletBase.h"

class BulletManager : public IRenderable
{
private:
	std::vector<Sprite*> sprites;
	std::vector<BulletBase*> bullets;
	SDL_Renderer* renderer = nullptr;

public:

private:
	BulletBase* CreateBullet(Sprite* bulletSprite, Vector2D position, Vector2D scale);

public:
	BulletManager(SDL_Renderer* renderer);

	void AddBullet(BulletBase* bullet);

	void Start();
	void Update();
	void Render();
	void Destroy();
};