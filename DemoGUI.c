#include <stdio.h>
#include <SDL2/SDL.h>

void DrawMatrix(SDL_Renderer *renderer, int width, int height, unsigned char **matrix)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			SDL_SetRenderDrawColor(renderer, matrix[y][x], matrix[y][x], matrix[y][x], 255);
			SDL_RenderDrawPoint(renderer, x, y);
		}
	}
	SDL_RenderPresent(renderer);
}

void StartDemoGUI(int width, int height, unsigned char **grayscaleImageMatrix, unsigned char **binarizedImageMatrix)
{
	SDL_Event event;
	SDL_Renderer *renderer;
	SDL_Window *window;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);

	DrawMatrix(renderer, width, height, grayscaleImageMatrix);

	while (1)
	{
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
		{
			break;
		}
		if (SDL_PollEvent(&event) && event.type == SDL_KEYDOWN)
		{
			DrawMatrix(renderer, width, height, binarizedImageMatrix);
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
