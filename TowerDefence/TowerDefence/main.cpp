#include <iostream>
#include "GameManager.h"
#include "Timer.h"

int main(int argc, char* argv[])
{
	GameManager* gameManager = new GameManager("Tower Defense", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	Timer* timer = new Timer();

	gameManager->Start();
	while (gameManager->IsRunning() == true)
	{
		gameManager->HandleEvent();
		gameManager->Update(timer->DeltaTime());
		gameManager->Render();

		timer->Tick();

		//Log the deltaTime
		//timer->LogDeltaTime();
	}
	gameManager->Destroy();

	return 0;
}