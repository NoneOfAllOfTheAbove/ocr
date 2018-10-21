#include <stdio.h>
#include <SDL2/SDL.h>

int demoGUIStep = 0;

void DrawMatrix(
	SDL_Renderer *renderer,
	int width,
	int height,
	unsigned char **matrix
)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			SDL_SetRenderDrawColor(
				renderer,
				matrix[y][x],
				matrix[y][x],
				matrix[y][x],
				255
			);
			SDL_RenderDrawPoint(renderer, x, y);
		}
	}
	SDL_RenderPresent(renderer);
}

void StartDemoGUI(
	int width,
	int height,
	unsigned char **grayscaleImageMatrix,
	unsigned char **binarizedImageMatrix,
	unsigned char *characters
)
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
		else if (SDL_PollEvent(&event) && event.type == SDL_KEYDOWN)
		{
			if(demoGUIStep == 0) {
				DrawMatrix(renderer, width, height, binarizedImageMatrix);
			}
			else if(demoGUIStep == 1) {
				for(size_t i = 0; i < sizeof(characters); i += 4)
				{
					printf("%d %d %d %d", characters[0], characters[1], characters[2], characters[3]);
					SDL_Rect srcrect;
					srcrect.x = characters[0];
					srcrect.y = characters[1];
					srcrect.w = characters[2] - srcrect.x;
					srcrect.h = characters[3] - srcrect.y;
					SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
					SDL_RenderFillRect(renderer, &srcrect);
				}
			}
			demoGUIStep++;
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
