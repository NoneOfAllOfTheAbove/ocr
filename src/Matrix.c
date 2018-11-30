#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>

unsigned char **CreateCharMatrix(int width, int height)
{
	unsigned char **matrix =
		(unsigned char **)malloc(sizeof(unsigned char *) * height);
	for (int i = 0; i < height; i++)
	{
		*(matrix + i) = (unsigned char *)malloc(sizeof(unsigned char) * width);
	}
	return matrix;
}

double **CreateDoubleMatrix(size_t line, size_t column)
{
	double **matrix = (double **)malloc(sizeof(double *) * line);
	if (matrix == NULL)
		exit(0);
	for (size_t i = 0; i < line; i++)
	{
		*(matrix + i) = (double *)malloc(sizeof(double) * column);
	}
	return matrix;
}

void FreeMatrix(double **matrix, size_t line)
{
	for (size_t i = 0; i < line; i++)
	{
		free(matrix[i]);
	}
	free(matrix);
}

unsigned char **GetSubMatrix(unsigned char **matrix, int x1, int y1, int x2, int y2)
{
	unsigned char **result = CreateCharMatrix(x2 - x1, y2 - y1);
	
	for(int y = 0; y < y2 - y1; y++)
	{
		for(int x = 0; x < x2 - x1; x++)
		{
			result[y][x] = matrix[y1 + y][x1 + x];
		}
	}

	return result;
}

unsigned char **ToSquareMatrix(unsigned char **matrix, int oldX, int oldY, int size)
{
	// Step 1: Put matrix in a new matrix of size a * (16 * 16) 	
	int side = oldX;
	if(oldY > oldX)
	{
		side = oldY;
	}
	if(side % size != 0)
	{
		side = (1 + side / size) * size;
	} else
	{
		side = (side / size) * size;	
	}

	unsigned char **result = CreateCharMatrix(side, side);
	
	for(int y = 0; y < side; y++)
	{
		for(int x = 0; x < side; x++)
		{
			result[y][x] = 0;
		}
	}
	int leftOffset = (side - oldX) / 2;
	int topOffset = (side - oldY) / 2;
	for(int y = 0; y < oldY; y++)
	{
		for(int x = 0; x < oldX; x++)
		{
			result[y + topOffset][x + leftOffset] = matrix[y][x];
		}
	}

	// Step 2: Scale down matrix with side > 16
	int scale = side / size;
	if(scale > 1)
	{
		unsigned char **resized = CreateCharMatrix(size, size);
		
		for(int y = 0; y < size; y++)
		{
			for(int x = 0; x < size; x++)
			{
				// 1 pixel in resized is scale pixel in result
				unsigned char sum = 0;
				for(int y1 = 0; y1 < scale; y1++)
				{
					for(int x1 = 0; x1 < scale; x1++)
					{
						sum += result[scale * y + y1][scale * x + x1];
					}
				}
				if(sum > 0)
				{
					resized[y][x] = 1;
				}
				else
				{
					resized[y][x] = 0;
				}
			}
		}

		result = resized;
	}

	return result;
}

void SaveMatrixAsImage(unsigned char **matrix, int width, int height, char *path)
{
	// Create SDL surface
	SDL_Surface *surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	int bpp = surface->format->BytesPerPixel;

	// Convert image to SDL surface
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
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
	IMG_SavePNG(surface, path);
	SDL_FreeSurface(surface);
}
