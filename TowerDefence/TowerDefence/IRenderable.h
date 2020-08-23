#pragma once

class IRenderable
{
protected:
	bool isActive = false;

public:
	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render()= 0;
	virtual void Destroy() = 0;

	bool IsActive() { return isActive; }
};