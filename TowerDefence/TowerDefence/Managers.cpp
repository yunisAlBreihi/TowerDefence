#include "Managers.h"

#pragma region Construction
Managers* Managers::instance = nullptr;

Managers::Managers(SDL_Renderer* renderer) 
{
	this->renderer = renderer;
}

Managers::~Managers()
{
	delete instance;
}
#pragma endregion Construction

#pragma region GetSet
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
#pragma endregion GetSet

#pragma region Manage
void Managers::AddManager(ManagerBase* managerBase)
{
	managers.push_back(managerBase);
}
#pragma endregion Manage

