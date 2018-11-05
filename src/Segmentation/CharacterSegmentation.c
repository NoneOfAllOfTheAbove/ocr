#include <stdio.h>
#include <stdlib.h>

#include "../Matrix.h"
#include "../Preprocessing/Preprocessing.h"
#include "Segmentation.h"

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

Text GetCharacters(Image image, Text text)
{
	unsigned char **matrix = CreateCharMatrix(image.width, image.height);
	for(int y = 0; y < image.height; y++)
	{
		for(int x = 0; x < image.width; x++)
		{
			matrix[y][x] = image.binarized[y][x];
		}
	}

	for(int i = 0; i < text.numberOfParagraphs; i++)
	{
		int lastY = 0;
		for(int j = 0; j < text.paragraphs[i].numberOfLines; j++)
		{
			Character *characters = (Character*)malloc(sizeof(Character) * 100);

			// Select area of the line
			int x1 = text.paragraphs[i].x;
			int y1 = lastY;
			int x2 = text.paragraphs[i].x + text.paragraphs[i].width;
			int y2 = text.paragraphs[i].lines[j].y;
			lastY = y2;

			// Look for characters
			int characterId = 0;
			for(int x = x1; x < x2; x++)
			{
				for(int y = y1; y < y2; y++)
				{
					if(matrix[y][x] == 1)
					{
						int cx1 = x, cy1 = y, cx2 = x, cy2 = y;
						__DetectCharacters(matrix, x, y, &cx1, &cy1, &cx2, &cy2);
						
						if(cx2 - cx1 != 0 && cy2 - cy1 != 0)
						{
							cx2 += 1;
							cy2 += 1;
							unsigned char **characterMatrix = GetSubMatrix(image.binarized, cx1, cy1, cx2, cy2);
							characterMatrix = ResizeMatrix(characterMatrix, cx2 - cx1, cy2 -  cy1);
							Character character;
							character.x = x;
							character.y = y;
							character.matrix = characterMatrix;
							characters[characterId] = character;
							characterId++;
						}
					}
				}
			}

			text.paragraphs[i].lines[j].characters = characters;
		}
	}

	return text;
}
