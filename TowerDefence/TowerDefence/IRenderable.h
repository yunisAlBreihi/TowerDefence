#pragma once
#include <iostream>

class IRenderable
{
public:
	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render()= 0;
	virtual void Destroy() = 0;
};