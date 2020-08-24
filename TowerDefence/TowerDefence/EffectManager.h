#pragma once
#include <SDL.h>
#include <vector>
#include "IRenderable.h"
#include "ManagerBase.h"
#include "Managers.h"
#include "ExplosionBase.h"

class EffectManager : public IRenderable , public ManagerBase
{
private:
	Managers* managers = nullptr;
	std::vector<ExplosionBase*> effects;

public:
	EffectManager();

	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;

	void AddEffect(ExplosionBase* effect);
	void ClearEffects();

	ExplosionBase* GetInactiveEffectOfType(BulletType bulletType);
};