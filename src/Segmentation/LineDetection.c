#include <stdio.h>

#include "../Matrix.h"

int** DetectLines(unsigned char **matrix, int **blocks, int blockNumber)
{
	int** lines = CreateIntMatrix(blockNumber, 4);

	for(int i = 0; i < blockNumber; i++)
	{
		int state = 0;
		int numberOfLines = 0;
		int x1 = blocks[i][0];
		int y1 = blocks[i][1];
		int x2 = blocks[i][2];
		int y2 = blocks[i][3];

		for(int y = y1; y < y2; y++)
		{
			if(state == 0)
			{
				int x = x1;
				while(x < x2 && matrix[y][x] != 1)
				{
					x++;
				}
				if(x == x2)
				{
					lines[i][numberOfLines + 1] = y;
					numberOfLines++;
					state = 1;
				}
			} 
			else
			{
				int x = x1;
				int blackPixel = 0;
				while(x < x2 && blackPixel == 0)
				{
					if(matrix[y][x] == 1)
					{
						blackPixel = 1;
					}
					x++;
				}
				if(blackPixel)
				{
					state = 0;
				}
			}
		}
	
		lines[i][0] = numberOfLines;
	
	}

	return lines;
}
