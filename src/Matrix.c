#include <stdio.h>
#include <stdlib.h>

int **CreateIntMatrix(int width, int height)
{
	int **matrix =
		(int **)malloc(sizeof(int *) * height);
	for (int i = 0; i < height; i++)
	{
		*(matrix + i) = (int *)malloc(sizeof(int) * width);
	}
	return matrix;
}

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
