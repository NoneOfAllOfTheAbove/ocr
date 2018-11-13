#include <stdio.h>
#include <SDL2/SDL_image.h>
#include "../Preprocessing/Preprocessing.h"

void SaveImage(unsigned char **matrix, int width, int height, char *path)
{
	// Create SDL surface
	SDL_Surface *surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	int bpp = surface->format->BytesPerPixel;

	// Convert image to SDL surface
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			int color = 255;
			if (matrix[y][x] == 1)
			{
				color = 0;
			}
			Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
			*(Uint32 *)p = SDL_MapRGB(surface->format, color, color, color);
		}
	}

	// Export SDL surface to file
	SDL_SaveBMP(surface, path);
}