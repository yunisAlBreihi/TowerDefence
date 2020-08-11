#include <iostream>
#include "Managers.h"

Managers::Managers(SDL_Renderer* renderer) : renderer(renderer)
{
}

Managers::~Managers()
{
}

void Managers::AddManager(ManagerBase* managerBase)
{
	managers.push_back(managerBase);
}

ManagerBase* Managers::GetManager(ManagerName managerName)
{
	for (ManagerBase* managerBase : managers)
	{
		if (managerName == managerBase->GetName())
		{
			if (managerBase == nullptr)
			{
				std::cout << "Found the manager, but it is not assigned yet!" << std::endl;
				return nullptr;
			}
			return managerBase;
		}
	}
	std::cout << "Could not find the specified manager in the list!" << std::endl;
	return nullptr;
}