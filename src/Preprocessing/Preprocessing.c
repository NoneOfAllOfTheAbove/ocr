#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <err.h>

#include "../Matrix.h"
#include "Preprocessing.h"

Image LoadImageAsGrayscale(Image image)
{
	// Load image
	//IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
	SDL_Surface *imageSurface;
	imageSurface = IMG_Load(image.path);
	if(!imageSurface)
	{
		errx(1, "%s", IMG_GetError());
	}
	image.width = imageSurface->w;
	image.height = imageSurface->h;

	// Create matrix
	unsigned char **matrix = CreateCharMatrix(
		imageSurface->w,
		imageSurface->h
	);

	// Fill matrix with grayscale's values of image
	for (int y = 0; y < imageSurface->h; y++)
	{
		for (int x = 0; x < imageSurface->w; x++)
		{
			Uint8 *p = (Uint8 *)imageSurface->pixels + y * imageSurface->pitch
				+ x * imageSurface->format->BytesPerPixel;
			Uint32 pixel = *(Uint32 *)p;

			Uint8 r, g, b;
			SDL_GetRGB(pixel, imageSurface->format, &r, &g, &b);
			matrix[y][x] = (0.3 * r) + (0.59 * g) + (0.11 * b);
		}
	}

	IMG_Quit();
	image.grayscale = matrix;
	return image;
}

Image BinarizeImage(Image image)
{
	// Otsu's method: https://en.wikipedia.org/wiki/Otsu%27s_method
	int thresholdShift = 15;

	// Prepare variables
	int histogram[256];
	int threshold = 0, var_max = 0, sum = 0, sumB = 0, q1 = 0, q2 = 0, u1 = 0, u2 = 0;
	
	// Prepare histogram
	for(int i = 0; i <= 255; i++)
	{
		histogram[i] = 0;
	}
	for (int y = 0; y < image.height; y++)
	{
		for (int x = 0; x < image.width; x++)
		{
			int value = image.grayscale[y][x];
			histogram[value]++;
		}
	}
	for(int i = 0; i <= 255; i++)
	{
		sum += i * histogram[i];
	}

	// Otsu's main algorithm
	for(int t = 0; t <= 255; t++)
	{
		q1 += histogram[t];
		if(q1 == 0)
		{
			continue;
		}
		q2 += (image.width * image.height) - q1;
		sumB += t * histogram[t];
		u1 = sumB / q1;
		u2 = (sum - sumB) / q2;
		int current = q1 * q2 * (u1 - u2) * (u1 - u2);

		if(current > var_max)
		{
			threshold = t;
			var_max = current;
		}
	}

	// Create binarized matrix
	unsigned char **matrix = CreateCharMatrix(image.width, image.height);
	for (int y = 0; y < image.height; y++)
	{
		for (int x = 0; x < image.width; x++)
		{
			if(image.grayscale[y][x] > threshold + thresholdShift)
			{
				matrix[y][x] = 0;
			}
			else
			{
				matrix[y][x] = 1;
			}
		}
	}
	image.binarized = matrix;
	return image;
}
