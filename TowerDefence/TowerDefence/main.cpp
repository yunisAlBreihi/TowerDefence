#include <iostream>
#include <SDL.h>
#include <SDL_image.h>


int main(int argc, char* argv[])
{
	bool gameOver = false;
	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Renderer* renderer;
	SDL_Event event;

	window = SDL_CreateWindow("Tower Defence", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	while (gameOver != true)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				gameOver = true;
			}
		}

		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}

	std::cout << "Game Over!" << std::endl;

	return 0;
}