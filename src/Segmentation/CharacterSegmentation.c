#include <stdio.h>
#include <stdlib.h>

#include "../Matrix.h"
#include "../Preprocessing/Preprocessing.h"
#include "Segmentation.h"

int __CountCharacters(unsigned char **matrix, int x1, int x2, int y1, int y2, int *sumCharactersWidth)
{
	int numberOfCharacters = 0;
	int state = 0;
	
	for(int x = x1; x < x2; x++)
	{
		// Check for black pixels on vertical line x
		int y = y1;
		while(y < y2 && matrix[y][x] != 1)
			y++;

		if(y != y2)
		{
			numberOfCharacters += (state == 0) ? 1 : 0;
			*sumCharactersWidth += (state == 1) ? 1 : 0;
			state = 1;
		}
		else
		{
			state = 0;
		}
	}

	return numberOfCharacters;
}

Text GetCharacters(Image image, Text text)
{
	for(int i = 0; i < text.numberOfParagraphs; i++)
	{
		for(int j = 0; j < text.paragraphs[i].numberOfLines; j++)
		{
			// Select area of the line
			int x1 = text.paragraphs[i].x;
			int y1 = text.paragraphs[i].lines[j].y1;
			int x2 = text.paragraphs[i].x + text.paragraphs[i].width;
			int y2 = text.paragraphs[i].lines[j].y2;

			// Count characters
			int sumCharactersWidth = 0;
			int numberOfCharacters = __CountCharacters(image.binarized, x1, x2, y1, y2, &sumCharactersWidth);
			Character *characters = (Character*)malloc(sizeof(Character) * 2 * numberOfCharacters);
			int averageCharactersWidth = sumCharactersWidth / numberOfCharacters;

			// Handle characters
			int cx1, cx2, cy1 = 0, cy2 = 0;
			int characterId = 0, state = 0;
			for(int x = x1; x < x2; x++)
			{
				// Check for black pixels on vertical line x
				int y = y1, foundBlackPixel = 0, yMin = 0, yMax = 0;
				while(y < y2)
				{
					if(!foundBlackPixel && image.binarized[y][x] == 1)
					{
						yMin = y;
						foundBlackPixel = 1;
					}
					if(image.binarized[y][x] == 1)
					{
						yMax = y + 1;
					}
					y++;
				}

				if(foundBlackPixel)
				{
					if(state == 0)
					{
						cx1 = x;
						cy1 = yMin;
						cy2 = yMax;
						state = 1;
					}
					else
					{
						if(yMin < cy1)
							cy1 = yMin;
						if(yMax > cy2)
							cy2 = yMax;
					}
				}
				else
				{
					if(state == 1)
					{
						cx2 = x;
						
						if(cx2 - cx1 >= 2 * averageCharactersWidth)
						{
							int mid = (cx2 - cx1) / 2;

							Character character;
							character.x1 = cx1;
							character.x2 = cx1 + mid;
							character.y1 = cy1;
							character.y2 = cy2;
							character.character = '\0';
							character.matrix = GetSubMatrix(image.binarized, cx1, cy1, cx1 + mid, cy2);
							character.matrix = ToSquareMatrix(character.matrix, mid, cy2 - cy1, 16);
							characters[characterId] = character;
							
							characterId++;
							numberOfCharacters++;
							
							Character character2;
							character2.x1 = 1 + cx1 + mid;
							character2.x2 = cx2;
							character2.y1 = cy1;
							character2.y2 = cy2;
							character2.character = '\0';
							character2.matrix = GetSubMatrix(image.binarized, 1 + cx1 + mid, cy1, cx2, cy2);
							character2.matrix = ToSquareMatrix(character2.matrix, mid - 1, cy2 - cy1, 16);
							characters[characterId] = character2;
						}
						else
						{
							Character character;
							character.x1 = cx1;
							character.x2 = cx2;
							character.y1 = cy1;
							character.y2 = cy2;
							character.character = '\0';
							character.matrix = GetSubMatrix(image.binarized, cx1, cy1, cx2, cy2);
							character.matrix = ToSquareMatrix(character.matrix, cx2 - cx1, cy2 - cy1, 16);
							characters[characterId] = character;	
						}

						characterId++;
						state = 0;

						//printf("Found character %d at %d %d %d %d \n\n", characterId, cx1, cx2, cy1, cy2);

					}
				}
			}

			// Update paragraph
			text.paragraphs[i].lines[j].numberOfCharacters = numberOfCharacters;
			text.paragraphs[i].lines[j].characters = characters;
		}
	}

	return text;
}
