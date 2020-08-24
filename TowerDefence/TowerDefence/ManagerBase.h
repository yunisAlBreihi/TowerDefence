#pragma once
#include "Enums.h"

class ManagerBase
{
protected:
	ManagerName name = ManagerName::NONE;

protected:

public:
	virtual ~ManagerBase() = 0;

	ManagerName GetName() { return name; }
};