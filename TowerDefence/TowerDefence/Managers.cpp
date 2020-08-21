#include "Managers.h"

Managers* Managers::instance = nullptr;

Managers::Managers(SDL_Renderer* renderer) 
{
	this->renderer = renderer;
}

Managers* Managers::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Managers;
	}
	return instance;
}

void Managers::SetRenderer(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

void Managers::AddManager(ManagerBase* managerBase)
{
	managers.push_back(managerBase);
}

