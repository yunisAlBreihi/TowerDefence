#pragma once
#include <vector>
#include "IRenderable.h"
#include "ManagerBase.h"
#include "Managers.h"
#include "UIBase.h"

class UIManager : public IRenderable, public ManagerBase
{
private:
	std::vector<UIBase*> uiObjects;

	bool gameOver = false;
	bool congratulations = false;

private:
	void RenderEndScreen(UIBase* uiBase);

public:
	UIManager();
	~UIManager();

	void Start() override;
	void Update(float deltaTime) override;
	void Render() override;
	void Destroy() override;

	void AddUIObject(UIBase* uiBase);

	void GameOver(bool visibility);
	void Congratulations(bool visibility);
};