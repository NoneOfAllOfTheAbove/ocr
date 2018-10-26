#include <stdio.h>
#include <SDL2/SDL.h>

void waitForKeyPressed()
{
	SDL_Event event;

	do
	{
		SDL_PollEvent(&event);
	} while(event.type != SDL_KEYDOWN);

	do
	{
		SDL_PollEvent(&event);
	} while(event.type != SDL_KEYUP);
}

void DrawMatrix(
	SDL_Renderer *renderer,
	int width,
	int height,
	unsigned char **matrix,
	int opacity
)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int color = 0;
			if(matrix[y][x] == 0)
			{
				color = 255;
			}
			SDL_SetRenderDrawColor(renderer, color, color, color, opacity);
			SDL_RenderDrawPoint(renderer, x, y);
		}
	}
	SDL_RenderPresent(renderer);
}

void StartDemoGUI(
	int width,
	int height,
	unsigned char **binarizedImageMatrix,
	int **blocks,
	int blockNumber,
	int **lines
)
{
	SDL_Renderer *renderer;
	SDL_Window *window;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);

	DrawMatrix(renderer, width, height, binarizedImageMatrix, 255);
	waitForKeyPressed();
	for(int i = 0; i < blockNumber; i++)
	{
		// Blocks
		SDL_Rect rect;
		rect.x = blocks[i][0];
		rect.y = blocks[i][1];
		rect.w = blocks[i][2] - blocks[i][0];
		rect.h = blocks[i][3] - blocks[i][1];
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(renderer, &rect);

		// Lines
		for(int j = 0; j < 4; j++)
		{
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderDrawLine(renderer, blocks[i][0], lines[i][j], blocks[i][2], lines[i][j]);
		}
	}
	SDL_RenderPresent(renderer);

	waitForKeyPressed();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
