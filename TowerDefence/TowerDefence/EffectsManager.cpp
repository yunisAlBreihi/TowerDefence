#include "EffectsManager.h"

EffectsManager::EffectsManager(Managers* managers) : managers(managers)
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

void EffectsManager::Update()
{
	if (effects.empty() == false)
	{
		for (EffectBase* effect : effects)
		{
			effect->Update();
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

void EffectsManager::AddEffect(EffectBase* effect)
{
	effects.push_back(effect);
}