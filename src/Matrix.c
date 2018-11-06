#include <stdio.h>
#include <stdlib.h>

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

unsigned char **ResizeMatrix(unsigned char **matrix, int oldX, int oldY, int yOffset)
{
	// Step 1: Put matrix in a new matrix of size a * (16 * 16) 	
	int side = oldX;
	if(oldY > oldX)
	{
		side = oldY;
	}
	if(side % 16 != 0)
	{
		side = (1 + side / 16) * 16;
	} else
	{
		side = (side / 16) * 16;	
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
	int topOffset = (16 - oldY);
	if(yOffset > 8)
	{
		topOffset = 0;
	}
	for(int y = 0; y < oldY; y++)
	{
		for(int x = 0; x < oldX; x++)
		{
			result[y + topOffset][x + leftOffset] = matrix[y][x];
		}
	}

	// Step 2: Scale down matrix with side > 16
	int scale = side / 16;
	if(scale > 1)
	{
		unsigned char **resized = CreateCharMatrix(16, 16);
		
		for(int y = 0; y < 16; y++)
		{
			for(int x = 0; x < 16; x++)
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

	result[0][0] = yOffset; 


	return result;
}
