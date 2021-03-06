#include "BulletManager.h"

#pragma region Construction
BulletManager::BulletManager()
{
	managers = Managers::GetInstance();
	name = ManagerName::BulletManager;
}
#pragma endregion Construction

#pragma region GameLoop
void BulletManager::Start()
{
    for (const auto& bullet : bullets)
    {
        bullet->Start();
    }
}

void BulletManager::Update(float deltaTime)
{
	for (const auto& bullet : bullets)
	{
		bullet->Update(deltaTime);
	}
}

void BulletManager::Render()
{
	for (const auto& bullet : bullets)
	{
		bullet->Render();
	}
}
#pragma endregion GameLoop

#pragma region ManageBullets
BulletBase* BulletManager::GetInactiveBulletOfType(BulletType bulletType)
{
	for (const auto& bullet : bullets)
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
		for (const auto& bullet : bullets)
		{
			bullet->Disable();
		}
	}
	bullets.clear();
}
#pragma endregion ManageBullets