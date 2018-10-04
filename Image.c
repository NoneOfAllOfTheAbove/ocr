#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void LoadImage(SDL_Surface **imageSurface, char imagePath[], int *imageWidth, int *imageHeight)
{
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
	SDL_Surface *s;
	s = IMG_Load(imagePath);
	*imageSurface = s;
	*imageWidth = (*imageSurface)->w;
	*imageHeight = (*imageSurface)->h;
}

void ImageToMatrix(SDL_Surface *imageSurface, double **matrix)
{
	int y, x;

	for (y = 0; y < imageSurface->h; y++)
	{
		for (x = 0; x < imageSurface->w; x++)
		{
			Uint8 *p = (Uint8 *)imageSurface->pixels + y * imageSurface->pitch + x * imageSurface->format->BytesPerPixel;
			Uint32 pixel = *(Uint32 *)p;

			Uint8 r, g, b;
			SDL_GetRGB(pixel, imageSurface->format, &r, &g, &b);
			matrix[y][x] = (double)(r + g + b) / (3.0 * 255.0);
		}
	}

	IMG_Quit();
}