#include <stdio.h>
#include <stdlib.h>

#include "../Matrix.h"
#include "../Stack.h"
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
	int horizontalStep = 150; 
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

void __GetBoundsOfParagraph(unsigned char **matrix, int x, int y, int width, int height, int *xMin, int *yMin, int *xMax, int *yMax)
{
	if (x >= width || x < 0 || y < 0 || y >= height || matrix[y][x] != 2)
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
	
	matrix[y][x] = 3;

	__GetBoundsOfParagraph(matrix, x + 1, y, width, height, xMin, yMin, xMax, yMax);
	__GetBoundsOfParagraph(matrix, x - 1, y, width, height, xMin, yMin, xMax, yMax);
	__GetBoundsOfParagraph(matrix, x, y + 1, width, height, xMin, yMin, xMax, yMax);
	__GetBoundsOfParagraph(matrix, x, y - 1, width, height, xMin, yMin, xMax, yMax);
}

void __CountParagraphs(unsigned char **matrix, int x, int y, int width, int height)
{
	Stack stack = StackCreate(width * height);
	int data[2] = {x, y};
	StackPush(&stack, data);

	while(!IsStackEmpty(&stack))
	{
		int *data = StackPop(&stack);
		int x = data[0];
		int y = data[1];

		if (x >= 0 && x < width && y >= 0 && y < height && matrix[y][x] == 1)
		{
			matrix[y][x] = 2;

			int right[2] = {x + 1, y};
			StackPush(&stack, right);
			int left[2] = {x - 1, y};
			StackPush(&stack, left);
			int top[2] = {x, y + 1};
			StackPush(&stack, top);
			int bottom[2] = {x, y - 1};
			StackPush(&stack, bottom);
		}
	}
}

Paragraph *IdentifyBlocks(unsigned char **blocksMap, int *blockNumber, int imageWidth, int imageHeight)
{
	// Make a copy of blocksMap to not alter it
	unsigned char **matrix = CreateCharMatrix(imageWidth, imageHeight);
	for (int y = 0; y < imageHeight; y++)
	{
		for (int x = 0; x < imageWidth; x++)
		{
			matrix[y][x] = blocksMap[y][x];
		}
	}

	// Count paragraphs, matrix[y][x] == 1 => matrix[y][x] == 2
	int numberOfParagraphs = 0;
	for(int y = 0; y < imageHeight; y++)
	{
		for(int x = 0; x < imageWidth; x++)
		{
			if(matrix[y][x] == 1)
			{
				__CountParagraphs(matrix, x, y, imageWidth, imageHeight);
				numberOfParagraphs++;
			}
		}
	}
	*blockNumber = numberOfParagraphs;

	// Register every paragraphs' bounds, matrix[y][x] == 2 => matrix[y][x] == 3
	int paragraphId = 0;
	int xMin, yMin, xMax, yMax;
	Paragraph *paragraphs = (Paragraph*)malloc(sizeof(Paragraph) * numberOfParagraphs); 

	for(int y = 0; y < imageHeight; y++)
	{
		for(int x = 0; x < imageWidth; x++)
		{
			if(matrix[y][x] == 2)
			{
				xMin = x, yMin = y, xMax = x, yMax = y;
				printf("CRASH 0 \n");
				__GetBoundsOfParagraph(matrix, x, y, imageWidth, imageHeight, &xMin, &yMin, &xMax, &yMax);
				printf("CRASH 1 \n");
				Paragraph paragraph;
				paragraph.x = xMin;
				paragraph.y = yMin;
				paragraph.width = xMax - xMin + 5;
				paragraph.height = yMax - yMin + 5;
				if (paragraph.width > imageWidth)
					paragraph.width = (xMax - xMin) + (imageWidth - xMax);
				if (paragraph.height > imageHeight)
					paragraph.height = (yMax - yMin) + (imageHeight - yMax);
				paragraphs[paragraphId] = paragraph;

				paragraphId++;
			}
		}
	}

	return paragraphs;
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
