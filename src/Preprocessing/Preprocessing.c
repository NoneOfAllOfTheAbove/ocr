#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <err.h>

#include "../Matrix.h"

unsigned char **ImageToGrayscale(
	char imagePath[],
	int *imageWidth,
	int *imageHeight
)
{
	// Load image
	//IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
	SDL_Surface *imageSurface;
	imageSurface = IMG_Load(imagePath);
	if(!imageSurface)
	{
		errx(1, "%s", IMG_GetError());
	}
	*imageWidth = imageSurface->w;
	*imageHeight = imageSurface->h;

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
	return matrix;
}

unsigned char **GrayscaleToBinarized(
	unsigned char **grayscaleImageMatrix,
	int imageWidth,
	int imageHeight
)
{
	// Otsu's method: https://en.wikipedia.org/wiki/Otsu%27s_method
	
	// Prepare variables
	int histogram[256];
	int threshold = 0, var_max = 0, sum = 0, sumB = 0, q1 = 0, q2 = 0, u1 = 0, u2 = 0;
	
	// Prepare histogram
	for(int i = 0; i <= 255; i++)
	{
		histogram[i] = 0;
	}
	for (int y = 0; y < imageHeight; y++)
	{
		for (int x = 0; x < imageWidth; x++)
		{
			int value = grayscaleImageMatrix[y][x];
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
		q2 += (imageWidth * imageHeight) - q1;
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
	unsigned char **matrix = CreateCharMatrix(imageWidth, imageHeight);
	for (int y = 0; y < imageHeight; y++)
	{
		for (int x = 0; x < imageWidth; x++)
		{
			if(grayscaleImageMatrix[y][x] > threshold)
			{
				matrix[y][x] = 0;
			}
			else
			{
				matrix[y][x] = 1;
			}
		}
	}

	return matrix;
}
