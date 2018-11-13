#include <stdio.h>

#include "Matrix.h"
#include "Image/Image.h"

void ___DetectCharacters(unsigned char **matrix, int x, int y, int *cx1, int *cy1, int *cx2, int *cy2)
{
	if (matrix[y][x] == 0)
	{
		return;
	}

	matrix[y][x] = 0;

	if (x < *cx1)
		*cx1 = x;

	if (x > *cx2)
		*cx2 = x;

	if (y < *cy1)
		*cy1 = y;

	if (y > *cy2)
		*cy2 = y;

	___DetectCharacters(matrix, x + 1, y, cx1, cy1, cx2, cy2);
	___DetectCharacters(matrix, x - 1, y, cx1, cy1, cx2, cy2);
	___DetectCharacters(matrix, x, y + 1, cx1, cy1, cx2, cy2);
	___DetectCharacters(matrix, x, y - 1, cx1, cy1, cx2, cy2);

	___DetectCharacters(matrix, x + 1, y + 1, cx1, cy1, cx2, cy2);
	___DetectCharacters(matrix, x - 1, y + 1, cx1, cy1, cx2, cy2);
	___DetectCharacters(matrix, x + 1, y - 1, cx1, cy1, cx2, cy2);
	___DetectCharacters(matrix, x - 1, y - 1, cx1, cy1, cx2, cy2);
}

void DetectCharacters(unsigned char **binarized, int imageWidth, int imageHeight)
{
	int i = 0;

	unsigned char **matrix = CreateCharMatrix(imageWidth, imageHeight);
	for (int y = 0; y < imageHeight; y++)
	{
		for (int x = 0; x < imageWidth; x++)
		{
			matrix[y][x] = binarized[y][x];
		}
	}

	for (int x = 0; x < imageWidth; x++)
	{
		for (int y = 0; y < imageHeight; y++)
		{
			if (matrix[y][x] == 1)
			{
				int cx1 = x, cy1 = y, cx2 = x, cy2 = y;
				___DetectCharacters(matrix, x, y, &cx1, &cy1, &cx2, &cy2);
				cx2 += 1;
				cy2 += 1;

				unsigned char **character = GetSubMatrix(binarized, cx1, cy1, cx2, cy2);
				unsigned char **character = ToSquareMatrix(character, cx2 - cx1, cy2 - cy1, 16);
				SaveImage(character, i + ".png");
			}
		}
	}
}