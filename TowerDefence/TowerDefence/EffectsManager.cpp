#include "EffectsManager.h"

EffectsManager::EffectsManager()
{
	name = ManagerName::EffectsManager;
}

void EffectsManager::Start()
{
	if (effects.empty() == false)
	{
		for (EffectBase* effect : effects)
		{
			effect->Start();
		}
	}
}

void EffectsManager::Update(float deltaTime)
{
	if (effects.empty() == false)
	{
		for (EffectBase* effect : effects)
		{
			effect->Update(deltaTime);
		}
	}
}

void EffectsManager::Render()
{
	if (effects.empty() == false)
	{
		for (EffectBase* effect : effects)
		{
			effect->Render();
		}
	}
}

void EffectsManager::Destroy()
{
	if (effects.empty() == false)
	{
		for (EffectBase* effect : effects)
		{
			effect->Destroy();
		}
	}
}

EffectBase* EffectsManager::GetInactiveEffectOfType(BulletType bulletType)
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

void EffectsManager::AddEffect(EffectBase* effect)
{
	effects.push_back(effect);
}

void EffectsManager::ClearEffects()
{
	effects.clear();
}