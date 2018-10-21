#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

unsigned char **CreateImageMatrix(int width, int height)
{
	unsigned char **matrix =
		(unsigned char **)malloc(sizeof(unsigned char *) * height);
	for (int i = 0; i < height; i++)
	{
		*(matrix + i) = (unsigned char *)malloc(sizeof(unsigned char) * width);
	}
	return matrix;
}

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
	*imageWidth = imageSurface->w;
	*imageHeight = imageSurface->h;

	// Create matrix
	unsigned char **matrix = CreateImageMatrix(
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
	// Create matrix
	unsigned char **matrix = CreateImageMatrix(imageWidth, imageHeight);

	// Compute average intensity
	int totalIntensity = 0;
	for (int y = 0; y < imageHeight; y++)
	{
		for (int x = 0; x < imageWidth; x++)
		{
			totalIntensity += grayscaleImageMatrix[y][x];
		}
	}
	int averageIntensity = totalIntensity / (imageWidth * imageHeight);

	// Fill matrix
	for (int y = 0; y < imageHeight; y++)
	{
		for (int x = 0; x < imageWidth; x++)
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

	return matrix;
}