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
		switch (managerName)
		{
		case ManagerName::NONE:
			break;
		case ManagerName::BulletManager:
			std::cout << "Could not find BulletManager in the list!" << std::endl;
			break;
		case ManagerName::EffectsManager:
			std::cout << "Could not find EffectsManager in the list!" << std::endl;
			break;
		case ManagerName::EnemyManager:
			std::cout << "Could not find EnemyManager in the list!" << std::endl;
			break;
		case ManagerName::GameManager:
			std::cout << "Could not find GameManager in the list!" << std::endl;
			break;
		case ManagerName::MapManager:
			std::cout << "Could not find MapManager in the list!" << std::endl;
			break;
		case ManagerName::SpriteManager:
			std::cout << "Could not find SpriteManager in the list!" << std::endl;
			break;
		case ManagerName::TextureManager:
			std::cout << "Could not find TextureManager in the list!" << std::endl;
			break;
		case ManagerName::TileManager:
			std::cout << "Could not find TileManager in the list!" << std::endl;
			break;
		case ManagerName::TowerManager:
			std::cout << "Could not find TowerManager in the list!" << std::endl;
			break;
		case ManagerName::LevelManager:
			std::cout << "Could not find LevelManager in the list!" << std::endl;
			break;
		case ManagerName::UIManager:
			std::cout << "Could not find UIManager in the list!" << std::endl;
			break;
		}
		return nullptr;
	};

	SDL_Renderer* GetRenderer() { return renderer; }
};