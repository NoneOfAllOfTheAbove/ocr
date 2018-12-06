#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <err.h>
#include <math.h>

#include "../Matrix.h"
#include "Preprocessing.h"
#include "../Segmentation/Segmentation.h"

Text Deskew(Image* image, Text text)
{
	int x1 = text.paragraphs[0].x;
	int x2 = text.paragraphs[0].x + text.paragraphs[0].width;
	int y1 = text.paragraphs[0].y;
	int y2 = text.paragraphs[0].y + text.paragraphs[0].height;
	
	int yLeft = y2;
	int yRight = y2;

	while (yLeft > y1 && text.blocksMap[yLeft][x1] == 0)
	{
		yLeft--;
	}
	while (yRight > y1 && text.blocksMap[yRight][x2 - 5] == 0)
	{
		yRight--;
	}

	text.deskewX1 = x1;
	text.deskewX2 = x2;
	text.deskewY1 = yLeft + 10;
	text.deskewY2 = yRight + 10;

	double width = (text.deskewY2 - text.deskewY1);
	double height = (x2 - x1);
	double angle = atan(width / height);
	printf("angle: %f\n", angle * 180.0 / 3.14159265);

	angle = -angle;
	unsigned char **newBinarized = CreateCharMatrix(image->width, image->height);
	for (int y = 0; y < image->height; y++)
	{
		for (int x = 0; x < image->width; x++)
		{
			newBinarized[y][x] = 0;
		}
	}
	for (int y = 0; y < image->height; y++)
	{
		for (int x = 0; x < image->width; x++)
		{
			int newX = cos(angle) * x - sin(angle) * y;
			int newY = sin(angle) * x + cos(angle) * y;
			if (newX >= 0 && newX < image->width && newY >= 0 && newY < image->height)
			{
				newBinarized[newY][newX] = image->binarized[y][x];
			}
		}
	}
	image->binarized = newBinarized;

	return text;
}