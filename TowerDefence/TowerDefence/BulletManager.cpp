#include "BulletManager.h"

BulletManager::BulletManager(SDL_Renderer* renderer) : renderer(renderer)
{
}

void BulletManager::Start()
{
    for (BulletBase* bullet : bullets)
    {
        bullet->Start();
    }
}

void BulletManager::Update()
{
	for (BulletBase* bullet : bullets)
	{
		bullet->Update();
	}
}

void BulletManager::Render()
{
	for (BulletBase* bullet : bullets)
	{
		bullet->Render();
	}
}

void BulletManager::Destroy()
{
	for (BulletBase* bullet : bullets)
	{
		bullet->Destroy();
	}
}

BulletBase* BulletManager::CreateBullet(Sprite* bulletSprite, Vector2D position, Vector2D scale)
{
	return nullptr;
}


void BulletManager::AddBullet(BulletBase* bullet)
{
	bullets.push_back(bullet);
}