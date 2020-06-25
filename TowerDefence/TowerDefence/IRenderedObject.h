#pragma once
class IRenderedObject
{
public:
	virtual void Start() = 0;
	virtual void Start(SDL_Renderer* renderer, std::string filePath, int width, int height) {};
	virtual void Update() = 0;
	virtual void Render()= 0;
	virtual void Destroy() = 0;
};