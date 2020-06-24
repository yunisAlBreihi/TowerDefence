#include <iostream>
#include "GameManager.h"


int main(int argc, char* argv[])
{
	GameManager* gameManager = new GameManager("Tower Defence", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

	while (gameManager->IsRunning() == true)
	{
		gameManager->HandleEvent();
		gameManager->Update();
		gameManager->Render();
	}

	gameManager->Destroy();

	return 0;
}