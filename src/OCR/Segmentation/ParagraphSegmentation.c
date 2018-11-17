#include <stdio.h>
#include <stdlib.h>

#include "../Matrix.h"
#include "../Preprocessing/Preprocessing.h"
#include "Segmentation.h"

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
	int horizontalStep = 1000; 
	int verticalStep = 300; 
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

void __GetBoundsOfBlock(unsigned char **matrix, int x, int y, int width, int height, int *xMin, int *yMin, int *xMax, int *yMax, int blockId)
{
	if(x >= width || x < 0 || y < 0 || y >= height || matrix[y][x] != blockId || matrix[y][x] == 0)
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
	
	matrix[y][x] = 0;

	__GetBoundsOfBlock(matrix, x + 1, y, width, height, xMin, yMin, xMax, yMax, blockId);
	__GetBoundsOfBlock(matrix, x - 1, y, width, height, xMin, yMin, xMax, yMax, blockId);
	__GetBoundsOfBlock(matrix, x, y + 1, width, height, xMin, yMin, xMax, yMax, blockId);
	__GetBoundsOfBlock(matrix, x, y - 1, width, height, xMin, yMin, xMax, yMax, blockId);
}

void __IdentifyBlocks(unsigned char **matrix, int x, int y, int width, int height, int blockId)
{
	//printf("%d %d \n", x, y);
	if(x < 0 || x >= width || y < 0 || y >= height || matrix[y][x] != 1)
	{
		return;
	}
	
	matrix[y][x] = blockId;

	__IdentifyBlocks(matrix, x + 1, y, width, height, blockId);
	__IdentifyBlocks(matrix, x - 1, y, width, height, blockId);
	__IdentifyBlocks(matrix, x, y + 1, width, height, blockId);
	__IdentifyBlocks(matrix, x, y - 1, width, height, blockId);
}

Paragraph* IdentifyBlocks(unsigned char** blocksMap, int *blockNumber, int imageWidth, int imageHeight)
{
	unsigned char **matrix = CreateCharMatrix(imageWidth, imageHeight);
	for (int y = 0; y < imageHeight; y++)
	{
		for (int x = 0; x < imageWidth; x++)
		{
			matrix[y][x] = blocksMap[y][x];
		}
	}

	// Count and mark every block with a unique id
	int numberOfBlocks = 0;
	unsigned char blockId = 2;
	for(int y = 0; y < imageHeight; y++)
	{
		for(int x = 0; x < imageWidth; x++)
		{
			if(matrix[y][x] == 1)
			{
				__IdentifyBlocks(matrix, x, y, imageWidth, imageHeight, blockId);
				blockId++;
				numberOfBlocks++;
			}
		}
	}
	*blockNumber = numberOfBlocks;

	// Register every block bounds
	int i = 0;
	int xMin, yMin, xMax, yMax;
	Paragraph *list = (Paragraph*)malloc(sizeof(Paragraph) * numberOfBlocks); 

	for(int y = 0; y < imageHeight; y++)
	{
		for(int x = 0; x < imageWidth; x++)
		{
			if(matrix[y][x] > 0)
			{
				xMin = x, yMin = y, xMax = x, yMax = y;
				__GetBoundsOfBlock(matrix, x, y, imageWidth, imageHeight, &xMin, &yMin, &xMax, &yMax, matrix[y][x]);
				
				Paragraph p;
				p.x = xMin;
				p.y = yMin;
				p.width = xMax - xMin + 5;
				p.height = yMax - yMin + 10;

				/*if (p.width > imageWidth)
					p.width = (xMax - xMin) + (imageWidth - xMax);
				if (p.height > imageHeight)
					p.height = (yMax - yMin) + (imageHeight - yMax);*/

				list[i] = p;
				
				i++;
			}
		}
	}

	return list;
}

Text GetParagraphs(Image image, Text text)
{
	int number = 0;
	text.blocksMap = RLSA(image.binarized, image.width, image.height);
	Paragraph *paragraphs = IdentifyBlocks(text.blocksMap, &number, image.width, image.height);

	text.numberOfParagraphs = number;
	text.paragraphs = paragraphs;
	return text;
}
