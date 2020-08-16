#include "UIManager.h"

UIManager::UIManager(Managers* managers)
{
	name = ManagerName::UIManager;
}

UIManager::~UIManager()
{
}

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
		//Only render GameOver or congratulations screen if they are active
		if (ui->GetSprite()->GetSpriteName() == SpriteName::GameOver)
		{
			if (gameOver == true)
			{
				ui->Render();
			}
		}
		else if (ui->GetSprite()->GetSpriteName() == SpriteName::Congratulations)
		{
			if (congratulations == true)
			{
				ui->Render();
			}
		}
		else
		{
			ui->Render();
		}
	}
}

void UIManager::Destroy()
{
}

void UIManager::AddUIObject(UIBase* uiBase)
{
	uiObjects.push_back(uiBase);
}

void UIManager::SetGameOverScreenVisibility(bool visibility)
{
	gameOver = visibility;
}

void UIManager::SetCongratulationsScreenVisibility(bool visibility)
{
	congratulations = visibility;
}
