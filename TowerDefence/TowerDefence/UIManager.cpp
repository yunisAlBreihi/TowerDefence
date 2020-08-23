#include "UIManager.h"

#pragma region Construction
UIManager::UIManager()
{
	name = ManagerName::UIManager;
}

UIManager::~UIManager()
{
}
#pragma endregion Construction

#pragma region GameLoop
void UIManager::Start()
{
}

void UIManager::Update(float deltaTime)
{
}

void UIManager::Render()
{
	for (UIBase* ui : uiObjects)
	{
		RenderEndScreen(ui);
	}
}

void UIManager::Destroy()
{
}
#pragma endregion GameLoop

#pragma region ManageUIObjects
void UIManager::AddUIObject(UIBase* uiBase)
{
	uiObjects.push_back(uiBase);
}
#pragma endregion ManageUIObjects

#pragma region EndScreen
void UIManager::RenderEndScreen(UIBase* uiBase)
{
	//Only render GameOver or congratulations screen if they are active
	if (uiBase->GetSprite()->GetSpriteName() == SpriteName::GameOver)
	{
		if (gameOver == true)
		{
			uiBase->Render();
		}
	}
	else if (uiBase->GetSprite()->GetSpriteName() == SpriteName::Congratulations)
	{
		if (congratulations == true)
		{
			uiBase->Render();
		}
	}
	else
	{
		uiBase->Render();
	}
}

void UIManager::GameOver(bool visibility)
{
	gameOver = visibility;
}

void UIManager::Congratulations(bool visibility)
{
	congratulations = visibility;
}
#pragma endregion EndScreen