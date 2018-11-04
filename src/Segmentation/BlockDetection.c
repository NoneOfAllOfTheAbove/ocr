#include <stdio.h>

#include "../Matrix.h"

int GetNumberHorizontalWhiteNeighbors(unsigned char **array, int x, int y, int maxPos, int step)
{
	int count = 0;
	int i = x + 1;
	while (i < maxPos && array[y][i] == 0)
	{
		count++;
		i++;
	}
	if(i == maxPos)
		count += step;

	i = x;
	while (i > 0 && array[y][i] == 0)
	{
		count++;
		i--;
	}
	if(i == 0)
		count += step;

	return count;
}

int GetNumberVerticalWhiteNeighbors(unsigned char **array, int x, int y, int maxPos, int step)
{
	int count = 0;
	int i = y + 1;
	while (i < maxPos && array[i][x] == 0)
	{
		count++;
		i++;
	}
	if(i == maxPos)
		count += step;

	i = y;
	while (i > 0 && array[i][x] == 0)
	{
		count++;
		i--;
	}
	if(i == 0)
		count += step;

	return count;
}

unsigned char **RLSA(unsigned char **binarizedImageMatrix, int imageWidth, int imageHeight)
{
	int horizontalStep = 20; 
	int verticalStep = 30; 
	unsigned char **horizontalResult = CreateCharMatrix(imageWidth, imageHeight);
	unsigned char **verticalResult = CreateCharMatrix(imageWidth, imageHeight);

	// Horizontal pass
	for(int y = 0; y < imageHeight; y++)
	{
		for(int x = 0; x < imageWidth; x++)
		{
			if(binarizedImageMatrix[y][x] == 0)
			{
				int n = GetNumberHorizontalWhiteNeighbors(binarizedImageMatrix, x, y, imageWidth, horizontalStep);
				if(n <= horizontalStep)
				{
					horizontalResult[y][x] = 1;
				} else {
					horizontalResult[y][x] = 0;
				}
			} else {
				horizontalResult[y][x] = 1;
			}
		}
	}

	// Vertical pass
	for(int y = 0; y < imageHeight; y++)
	{
		for(int x = 0; x < imageWidth; x++)
		{
			if(horizontalResult[y][x] == 0)
			{
				int n = GetNumberVerticalWhiteNeighbors(horizontalResult, x, y, imageHeight, verticalStep);
				if(n <= verticalStep)
				{
					verticalResult[y][x] = 1;
				} else {
					verticalResult[y][x] = 0;
				}
			} else {
				verticalResult[y][x] = 1;
			}
		}
	}

	return verticalResult;
}

void __IdentifyBlocks(unsigned char **matrix, int x, int y, int width, int height, int *xMin, int *yMin, int *xMax, int *yMax, int k)
{
	if(x >= width || x < 0 || y < 0 || y >= height || matrix[y][x] != 1)
	{
		return;
	}

	if(x > *xMax)
	{
		*xMax = x;
	}
	if(y > *yMax)
	{
		*yMax = y;
	}
	if(x < *xMin)
	{
		*xMin = x;
	}
	if(y < *yMin)
	{
		*yMin = y;
	}

	matrix[y][x] = k;
	__IdentifyBlocks(matrix, x + 1, y, width, height, xMin, yMin, xMax, yMax, k);
	__IdentifyBlocks(matrix, x - 1, y, width, height, xMin, yMin, xMax, yMax, k);
	__IdentifyBlocks(matrix, x, y + 1, width, height, xMin, yMin, xMax, yMax, k);
	__IdentifyBlocks(matrix, x, y - 1, width, height, xMin, yMin, xMax, yMax, k);
}

int **IdentifyBlocks(unsigned char** matrix, int *blockNumber, int imageWidth, int imageHeight)
{
	int i = 0;
	int xMin, yMin, xMax, yMax;
	int **blocks = CreateIntMatrix(100, 4);
	for(int y = 0; y < imageHeight; y++)
	{
		for(int x = 0; x < imageWidth; x++)
		{
			if(matrix[y][x] == 1)
			{
				xMin = x, yMin = y, xMax = x, yMax = y;
				__IdentifyBlocks(matrix, x, y, imageWidth, imageHeight, &xMin, &yMin, &xMax, &yMax, i + 2);
				
				blocks[i][0] = xMin;
				blocks[i][1] = yMin;
				blocks[i][2] = xMax + 5;
				blocks[i][3] = yMax + 5;

				if(xMax + 5 > imageWidth)
					blocks[i][2] = imageWidth;
				if(yMax + 5 > imageHeight)
					blocks[i][3] = imageHeight;

				i++;
			}
		}
	}

	*blockNumber = i;
	return blocks;
}

int** DetectBlocks(unsigned char** matrix, int *blockNumber, int imageWidth, int imageHeight)
{
	int number = 0;

	unsigned char **blocksMap = RLSA(matrix, imageWidth, imageHeight);
	int **blocks = IdentifyBlocks(blocksMap, &number, imageWidth, imageHeight);

	*blockNumber = number;
	return blocks;
}
