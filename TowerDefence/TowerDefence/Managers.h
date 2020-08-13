#pragma once
#include <vector>
#include <SDL.h>
#include <iostream>
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

	template<typename Manager>
	Manager* GetManager(ManagerName managerName)
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
				return (Manager*)managerBase;
			}
		}
		std::cout << "Could not find the specified manager in the list!" << std::endl;
		return nullptr;
	};

	SDL_Renderer* GetRenderer() { return renderer; }
};