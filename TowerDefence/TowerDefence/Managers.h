#pragma once
#include <vector>
#include "ManagerBase.h"
#include "Enums.h"

class Managers
{
private:
	std::vector<ManagerBase*> managers;

public:
	Managers();
	~Managers();

	void AddManager(ManagerBase* managerBase);
	ManagerBase* GetManager(ManagerName managerName);
};