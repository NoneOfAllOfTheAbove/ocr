#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <err.h>
#include <math.h>

#include "../Matrix.h"
#include "Preprocessing.h"
#include "../Segmentation/Segmentation.h"

Text Deskew(Image image, Text text)
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

	return text;
}