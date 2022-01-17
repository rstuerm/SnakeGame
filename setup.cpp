#include <iostream>
#include <SDL.h>
#include "setup.h"
#include "constants.h"

bool Window::InitScreen()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) > 0)
	{
		std::cout << "SDL_Init failed with error: " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	window = SDL_CreateWindow(
		"Snake Game",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_OPENGL
	);

	if (window == nullptr)
	{
		std::cout << "unable to create the main window. Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return EXIT_FAILURE;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	return true;
}

void Window::ShutdownScreen()
{
	if (window != nullptr)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
	}

	if (renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	SDL_Quit();
}

void Window::ClearScreen()
{
	SDL_SetRenderDrawColor(
		renderer, 
		Colors::BLACK.r, 
		Colors::BLACK.g, 
		Colors::BLACK.b, 
		Colors::BLACK.a
	);
	SDL_RenderClear(renderer);
}

void Window::UpdateScreen()
{
	SDL_RenderPresent(renderer);
}

