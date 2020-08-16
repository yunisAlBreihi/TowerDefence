#include "BulletManager.h"

BulletManager::BulletManager(Managers* managers) : managers(managers)
{
	name = ManagerName::BulletManager;
}

void BulletManager::Start()
{
    for (BulletBase* bullet : bullets)
    {
        bullet->Start();
    }
}

void BulletManager::Update(float deltaTime)
{
	for (BulletBase* bullet : bullets)
	{
		bullet->Update(deltaTime);
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

void BulletManager::AddBullet(BulletBase* bullet)
{
	bullets.push_back(bullet);
}

void BulletManager::ClearBullets()
{
	if (bullets.empty() == false)
	{
		for (auto bullet : bullets)
		{
			bullet->Destroy();
		}
	}

	bullets.clear();
}
