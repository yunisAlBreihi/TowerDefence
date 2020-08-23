#include "BulletManager.h"

#pragma region Construction
BulletManager::BulletManager()
{
	managers = Managers::GetInstance();
	name = ManagerName::BulletManager;
}

BulletManager::~BulletManager()
{
}
#pragma endregion Construction

#pragma region GameLoop
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
#pragma endregion GameLoop

#pragma region ManageBullets
BulletBase* BulletManager::GetInactiveBulletOfType(BulletType bulletType)
{
	for (auto bullet : bullets)
	{
		if (bullet->IsActive() == false)
		{
			if (bullet->GetType() == bulletType)
			{
				return bullet;
			}
		}
	}
	std::cout << "Could not find a bullet that is inactive, returning nullptr" << std::endl;
	return nullptr;
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
#pragma endregion ManageBullets
