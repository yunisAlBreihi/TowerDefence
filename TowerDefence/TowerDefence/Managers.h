#pragma once
#include <vector>
#include <SDL.h>
#include "ManagerBase.h"
#include "Enums.h"

class Managers
{
private:
	std::vector<ManagerBase*> managers;
	SDL_Renderer* renderer;

public:
	Managers(SDL_Renderer* renderer);
	~Managers();

	void AddManager(ManagerBase* managerBase);
	ManagerBase* GetManager(ManagerName managerName);
	SDL_Renderer* GetRenderer() { return renderer; }
};