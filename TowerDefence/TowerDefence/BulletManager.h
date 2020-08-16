#pragma once
#include <vector>
#include "ManagerBase.h"
#include "Managers.h"
#include "BulletBase.h"

class BulletManager : public IRenderable , public ManagerBase
{
private:
	Managers* managers = nullptr;
	std::vector<Sprite*> sprites;
	std::vector<BulletBase*> bullets;

public:

private:

public:
	BulletManager(Managers* managers);

	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Destroy() override;

	void AddBullet(BulletBase* bullet);
	void ClearBullets();
};