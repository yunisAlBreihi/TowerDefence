#include "EffectManager.h"

#pragma region Construction
EffectManager::EffectManager()
{
	name = ManagerName::EffectsManager;
}

EffectManager::~EffectManager()
{
}
#pragma endregion Construction

#pragma region GameLoop
void EffectManager::Start()
{
	if (effects.empty() == false)
	{
		for (ExplosionBase* effect : effects)
		{
			effect->Start();
		}
	}
}

void EffectManager::Update(float deltaTime)
{
	if (effects.empty() == false)
	{
		for (ExplosionBase* effect : effects)
		{
			effect->Update(deltaTime);
		}
	}
}

void EffectManager::Render()
{
	if (effects.empty() == false)
	{
		for (ExplosionBase* effect : effects)
		{
			effect->Render();
		}
	}
}

void EffectManager::Destroy()
{
	if (effects.empty() == false)
	{
		for (ExplosionBase* effect : effects)
		{
			effect->Destroy();
		}
	}
}
#pragma endregion GameLoop

#pragma region ManageEffects
ExplosionBase* EffectManager::GetInactiveEffectOfType(BulletType bulletType)
{
	for (auto effect : effects)
	{
		if (effect->IsActive() == false)
		{
			if (effect->GetType() == bulletType)
			{
				return effect;
			}
		}
	}
	std::cout << "Could not find an effect that is inactive, returning nullptr" << std::endl;
	return nullptr;
}

void EffectManager::AddEffect(ExplosionBase* effect)
{
	effects.push_back(effect);
}

void EffectManager::ClearEffects()
{
	effects.clear();
}
#pragma endregion ManageEffects