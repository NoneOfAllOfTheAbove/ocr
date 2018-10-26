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
	unsigned char **blocksMap,
	int **blocks,
	int **lines
)
{
	SDL_Event event;
	SDL_Renderer *renderer;
	SDL_Window *window;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);

	DrawMatrix(renderer, width, height, binarizedImageMatrix, 255);
	//waitForKeyPressed();
	//DrawMatrix(renderer, width, height, blocksMap, 255);
	waitForKeyPressed();
	for(int i = 0; i < 80; i += 4)
	{
		// Blocks
		SDL_Rect rect;
		rect.x = blocks[0][i];
		rect.y = blocks[0][i + 1];
		rect.w = blocks[0][i + 2] - blocks[0][i];
		rect.h = blocks[0][i + 3] - blocks[0][i + 1];
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(renderer, &rect);

		// Lines
		for(int i = 0; i < 4; i++)
		{
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderDrawLine(renderer, blocks[0][0], lines[0][i], blocks[0][2], lines[0][i]);
		}
	}
	SDL_RenderPresent(renderer);

	while (1)
	{
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
		{
			break;
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
