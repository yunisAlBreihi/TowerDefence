#pragma once
#include <SDL.h>
#include <vector>
#include "IRenderable.h"
#include "ManagerBase.h"
#include "Managers.h"
#include "EffectBase.h"

class EffectsManager : public IRenderable , public ManagerBase
{
private:
	Managers* managers = nullptr;
	std::vector<EffectBase*> effects;

public:

private:

public:
	EffectsManager();

	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Destroy() override;

	EffectBase* GetInactiveEffectOfType(BulletType bulletType);

	void AddEffect(EffectBase* effect);
	void ClearEffects();
};