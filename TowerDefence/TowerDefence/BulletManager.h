#pragma once
#include <vector>
#include "ManagerBase.h"
#include "Managers.h"
#include "BulletBase.h"

class BulletManager : public IRenderable , public ManagerBase
{
private:
	Managers* managers = nullptr;
	std::vector<BulletBase*> bullets;

private:

public:
	BulletManager();
	~BulletManager();

	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Destroy() override;

	void AddBullet(BulletBase* bullet);
	void ClearBullets();

	BulletBase* GetInactiveBulletOfType(BulletType bulletType);
};