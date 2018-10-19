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

double** CreateMatrix(int width, int height)
{
	double** matrix = (double **)malloc(sizeof(double *) * height);
	for (int i = 0; i < width; i++)
	{
		*(matrix + i) = (double *)malloc(sizeof(double) * height);
	}

	return matrix;
}

void ImageToMatrices(SDL_Surface *imageSurface, double **grayscaleImageMatrix, double **binarizedImageMatrix)
{
	int y, x;
	int currentIntensity = 0;
	int totalIntensity = 0;

	for (y = 0; y < imageSurface->h; y++)
	{
		for (x = 0; x < imageSurface->w; x++)
		{
			Uint8 *p = (Uint8 *)imageSurface->pixels + y * imageSurface->pitch + x * imageSurface->format->BytesPerPixel;
			Uint32 pixel = *(Uint32 *)p;

			Uint8 r, g, b;
			SDL_GetRGB(pixel, imageSurface->format, &r, &g, &b);
			currentIntensity = (double)(r + g + b) / (3.0 * 255.0);
			totalIntensity = totalIntensity + currentIntensity;
			grayscaleImageMatrix[y][x] = currentIntensity;
		}
	}

	int averageIntensity = totalIntensity / (imageSurface->h * imageSurface->w);
	for (y = 0; y < imageSurface->h; y++)
	{
		for (x = 0; x < imageSurface->w; x++)
		{
			if (grayscaleImageMatrix[y][x] > averageIntensity)
			{
				binarizedImageMatrix[y][x] = 1;
			} else {
				binarizedImageMatrix[y][x] = 0;
			}
		}
	}
	
	IMG_Quit();
}
