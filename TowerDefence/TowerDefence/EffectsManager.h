#pragma once
#include <SDL.h>
#include <vector>
#include "IRenderable.h"
#include "EffectBase.h"

class EffectsManager : public IRenderable
{
private:
	std::vector<EffectBase*> effects;
	SDL_Renderer* renderer = nullptr;

public:

private:

public:
	EffectsManager(SDL_Renderer* renderer);

	void Start();
	void Update();
	void Render();
	void Destroy();

	void AddEffect(EffectBase* effect);
};

