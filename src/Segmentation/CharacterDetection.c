#include <stdio.h>

#include "../Matrix.h"

void DetectCharacters(unsigned char **binarizedImageMatrix, int imageWidth, int imageHeight, int **blocks, int blockNumber, int **lines)
{
	unsigned char **matrix = CreateCharMatrix(imageWidth, imageHeight);
	for(int y = 0; y < imageHeight; y++)
	{
		for(int x = 0; x < imageWidth; x++)
		{
			matrix[y][x] = binarizedImageMatrix[y][x];
		}
	}

	for(int i = 0; i < blockNumber; i++)
	{
		int lastY = 0;
		for(int j = 1; j < lines[i][0] + 1; j++)
		{
			// Select area of the line
			int x1 = blocks[i][0];
			int y1 = lastY;
			int x2 = blocks[i][2];
			int y2 = lines[i][j];
			lastY = y2;

			// Look for characters
			for(int y = y1; y < y2; y++)
			{
				for(int x = x1; x < x2; x++)
				{
					// find cx1 cy1 cx2 cy2
					// unsigned char **characterMatrix = GetSubMatrix(matrix, cx1, cy1, cx2, cy2);
					// put in matrix of 16x16 RESIZE
					// OnCharacterDetected(characterMatrix);
				}
			}
		}
	}
}
