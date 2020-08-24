#include "EffectManager.h"

#pragma region Construction
EffectManager::EffectManager()
{
	name = ManagerName::EffectsManager;
}
#pragma endregion Construction

#pragma region GameLoop
void EffectManager::Start()
{
	for (const auto& effect : effects)
	{
		effect->Start();
	}
}

void EffectManager::Update(float deltaTime)
{
	for (const auto& effect : effects)
	{
		effect->Update(deltaTime);
	}
}

void EffectManager::Render()
{
		for (const auto& effect : effects)
		{
			effect->Render();
		}
}
#pragma endregion GameLoop

#pragma region ManageEffects
ExplosionBase* EffectManager::GetInactiveEffectOfType(BulletType bulletType)
{
	for (const auto& effect : effects)
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