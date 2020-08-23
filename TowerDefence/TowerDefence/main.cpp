#include <iostream>
#include "GameManager.h"
#include "Timer.h"

int main(int argc, char* argv[])
{
	GameManager* managerGame = new GameManager("Tower Defense", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	Timer* timer = new Timer();

	managerGame->Start();
	while (managerGame->IsRunning() == true)
	{
		managerGame->HandleEvent();
		managerGame->Update(timer->GetDeltaTime());
		managerGame->Render();
		timer->Tick();
	}
	managerGame->Destroy();

	return 0;
}