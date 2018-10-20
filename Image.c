#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

unsigned char **CreateImageMatrix(int imageWidth, int imageHeight)
{
	unsigned char **matrix;
	if (imageWidth <= imageHeight)
	{
		matrix = (unsigned char **)malloc(sizeof(unsigned char *) * imageHeight);
		for (int i = 0; i < imageWidth; i++)
		{
			*(matrix + i) = (unsigned char *)malloc(sizeof(unsigned char) * imageHeight);
		}
	}
	else
	{
		matrix = (unsigned char **)malloc(sizeof(unsigned char *) * imageWidth);
		for (int i = 0; i < imageHeight; i++)
		{
			*(matrix + i) = (unsigned char *)malloc(sizeof(unsigned char) * imageWidth);
		}
	}

	return matrix;
}

unsigned char **ImageToGrayscale(char imagePath[], int *imageWidth, int *imageHeight)
{
	// Load image
	//IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
	SDL_Surface *imageSurface;
	imageSurface = IMG_Load(imagePath);
	*imageWidth = imageSurface->w;
	*imageHeight = imageSurface->h;

	// Create matrix
	unsigned char **matrix = CreateImageMatrix(imageSurface->w, imageSurface->h);

	// Fill matrix with grayscale's values of image
	for (int y = 0; y < imageSurface->h; y++)
	{
		for (int x = 0; x < imageSurface->w; x++)
		{
			Uint8 *p = (Uint8 *)imageSurface->pixels + y * imageSurface->pitch + x * imageSurface->format->BytesPerPixel;
			Uint32 pixel = *(Uint32 *)p;

			Uint8 r, g, b;
			SDL_GetRGB(pixel, imageSurface->format, &r, &g, &b);
			if (imageSurface->w <= imageSurface->h)
			{
				matrix[x][y] = (r + g + b) / 3;
			} else {
				matrix[y][x] = (r + g + b) / 3;
			}
		}
	}

	IMG_Quit();
	return matrix;
}

unsigned char **GrayscaleToBinarized(unsigned char **grayscaleImageMatrix, int imageWidth, int imageHeight)
{
	// Create matrix
	unsigned char **matrix = CreateImageMatrix(imageWidth, imageHeight);

	// Compute average intensity
	int totalIntensity = 0;
	for (int y = 0; y < imageHeight; y++)
	{
		for (int x = 0; x < imageWidth; x++)
		{
			if (imageWidth <= imageHeight)
			{
				totalIntensity += grayscaleImageMatrix[x][y];
			} else {
				totalIntensity += grayscaleImageMatrix[y][x];
			}
		}
	}
	int averageIntensity = totalIntensity / (imageWidth * imageHeight);

	// Fill matrix
	for (int y = 0; y < imageHeight; y++)
	{
		for (int x = 0; x < imageWidth; x++)
		{
			if (imageWidth <= imageHeight)
			{
				if (grayscaleImageMatrix[x][y] > averageIntensity)
				{
					matrix[x][y] = 255;
				}
				else
				{
					matrix[x][y] = 0;
				}
			}
			else
			{
				if (grayscaleImageMatrix[y][x] > averageIntensity)
				{
					matrix[y][x] = 255;
				}
				else
				{
					matrix[y][x] = 0;
				}
			}
		}
	}

	return matrix;
}