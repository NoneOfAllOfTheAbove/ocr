#include <stdio.h>

#include "../Matrix.h"

void __DetectCharacters(unsigned char **matrix, int x, int y, int *cx1, int *cy1, int *cx2, int *cy2)
{
	if(matrix[y][x] == 0)
	{
		return;
	}

	matrix[y][x] = 0;
	
	if(x < *cx1)
		*cx1 = x;

	if(x > *cx2)
		*cx2 = x;

	if(y < *cy1)
		*cy1 = y;

	if(y > *cy2)
		*cy2 = y;
	
	__DetectCharacters(matrix, x + 1, y, cx1, cy1, cx2, cy2);
	__DetectCharacters(matrix, x - 1, y, cx1, cy1, cx2, cy2);
	__DetectCharacters(matrix, x, y + 1, cx1, cy1, cx2, cy2);
	__DetectCharacters(matrix, x, y - 1, cx1, cy1, cx2, cy2);
	
	__DetectCharacters(matrix, x + 1, y + 1, cx1, cy1, cx2, cy2);
	__DetectCharacters(matrix, x - 1, y + 1, cx1, cy1, cx2, cy2);
	__DetectCharacters(matrix, x + 1, y - 1, cx1, cy1, cx2, cy2);
	__DetectCharacters(matrix, x - 1, y - 1, cx1, cy1, cx2, cy2);

}

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
			for(int x = x1; x < x2; x++)
			{
				for(int y = y1; y < y2; y++)
				{
					if(matrix[y][x] == 1)
					{
						int cx1 = x, cy1 = y, cx2 = x, cy2 = y;
						__DetectCharacters(matrix, x, y, &cx1, &cy1, &cx2, &cy2);
						//printf("%d %d %d %d\n", cx1, cy1, cx2, cy2);
						if(cx2 - cx1 != 0 && cy2 - cy1 != 0)
						{
							cx2 += 1;
							cy2 += 1;
							unsigned char **characterMatrix = GetSubMatrix(binarizedImageMatrix, cx1, cy1, cx2, cy2);
							printf("\n");	
							for(int b = 0; b < cy2 - cy1; b++)
							{
								for(int a = 0; a < cx2 - cx1; a++)
								{
									if(characterMatrix[b][a] == 1)
									{
										printf("%d ", characterMatrix[b][a]);
									} else {
										printf("  ");
									}
								}
								printf("\n");
							}
						}
						// put in matrix of 16x16 (RESIZE)
					}
				}
			}
		}
	}
}
