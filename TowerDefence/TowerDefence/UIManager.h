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

public:
private:
public:
	UIManager(Managers* managers);
	~UIManager();

	void Start() override;
	void Update() override;
	void Render() override;
	void Destroy() override;

	void AddUIObject(UIBase* uiBase);

	void SetGameOverScreenVisibility(bool visibility);
	void SetCongratulationsScreenVisibility(bool visibility);
};