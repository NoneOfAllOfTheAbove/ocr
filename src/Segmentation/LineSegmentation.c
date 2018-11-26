#include <stdio.h>
#include <stdlib.h>

#include "../Matrix.h"
#include "../Preprocessing/Preprocessing.h"
#include "Segmentation.h"

int CountLines(unsigned char **matrix, int x1, int x2, int y1, int y2)
{
	int state = 0;
	int space = 0;
	int number = 0;

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
				space++;
				if(space > 2)
				{
					number++;
					state = 1;
					space = 0;
				}
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

	return number;
}

Text GetLines(Image image, Text text)
{
	for(int i = 0; i < text.numberOfParagraphs; i++)
	{
		// Prepare data
		int x1 = text.paragraphs[i].x;
		int y1 = text.paragraphs[i].y;
		int x2 = text.paragraphs[i].x + text.paragraphs[i].width;
		int y2 = text.paragraphs[i].y + text.paragraphs[i].height;
		int numberOfLines = CountLines(image.binarized, x1, x2, y1, y2);
		Line* lines = (Line*)malloc(sizeof(Line) * numberOfLines);

		int state = 0, space = 0;
		int lineId = 0;
		int topY = y1; 
		for(int y = y1; y < y2; y++)
		{
			if(state == 0)
			{
				int x = x1;
				while(x < x2 && image.binarized[y][x] != 1)
				{
					x++;
				}

				// If the horizontal line y is only composed of white pixels
				if(x == x2)
				{
					space++;
					if(space > 2)
					{
						// Create a line
						Line line;
						line.y1 = topY;
						line.y2 = y;
						lines[lineId] = line;
						lineId++;

						state = 1;
						space = 0;
					}
				}
			} 
			else
			{
				int x = x1;
				int blackPixel = 0;
				while(x < x2 && blackPixel == 0)
				{
					blackPixel = (image.binarized[y][x] == 1) ? 1 : 0;
					x++;
				}

				// If there is a black pixel on the horizontal line y
				if(blackPixel)
				{
					topY = y;
					state = 0;
				}
			}
		}

		// Update paragraph
		text.paragraphs[i].numberOfLines = numberOfLines;
		text.paragraphs[i].lines = lines;
	}

	return text;
}
