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
	// Prepare variables
	float histogram[256] = {0.0F};
	int threshold = 0;
	
	// Prepare histogram
	for (int y = 0; y < image.height; y++)
	{
		for (int x = 0; x < image.width; x++)
		{
			int value = image.grayscale[y][x];
			histogram[value]++;
		}
	}

	// Otsu's algorithm (https://en.wikipedia.org/wiki/Otsu%27s_method)
	for(int i = 0; i < 256; i++)
	{
		histogram[i] /= (image.width * image.height);
	}
	
	float ut = 0;
	for (int i = 0; i < 256; i++)
	{
		ut += i * histogram[i];
	}

	int max_k = 0;
	float max_sigma_k = 0;
	for(int k = 0; k < 256; k++)
	{
		float wk = 0;
		for(int i = 0; i <= k; i++)
		{
			wk += histogram[i];
		}
		float uk = 0;
		for(int i = 0; i <= k; i++)
		{
			uk += i * histogram[i];
		}

		float sigma_k = 0;
		if(wk != 0 && wk != 1)
		{
			sigma_k = ((ut * wk - uk) * (ut * wk - uk)) / (wk * (1 - wk));
		}
		if(sigma_k > max_sigma_k)
		{
			max_k = k;
			max_sigma_k = sigma_k;
		}
	}
	threshold = max_k;

	// Create binarized matrix
	unsigned char **matrix = CreateCharMatrix(image.width, image.height);
	for (int y = 0; y < image.height; y++)
	{
		for (int x = 0; x < image.width; x++)
		{
			if(image.grayscale[y][x] > 251)
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
