#include <stdio.h>
#include <stdlib.h>

#include "../Matrix.h"
#include "../Preprocessing/Preprocessing.h"
#include "Segmentation.h"
#include "WordSegmentation.h"

Character __PrepareCharacter(int l, int k, int c, int cx1, int cx2, int cy1, int cy2, unsigned char **matrix)
{
	Character character;
	character.x1 = cx1;
	character.x2 = cx2;
	character.y1 = cy1;
	character.y2 = cy2;
	character.character = '\0';
	unsigned char **sub = GetSubMatrix(matrix, cx1, cy1, cx2, cy2);
	unsigned char **normalized = ToSquareMatrix(sub, cx2 - cx1, cy2 - cy1, 16);
	character.matrix = normalized;

	/*if(k == 1 && c == 0 && l == 0)
	{
		unsigned char **test = GetSubMatrix(matrix, cx1, cy1, cx2, cy2);
		printf("- %d %d %d %d \n", cx1, cx2, cy1, cy2);
		for(int y = 0; y < cy2 - cy1; y++)
		{
			for(int x = 0; x < cx2 - cx1; x++)
			{
				printf("%d ", test[y][x]);
			}
			printf("\n");
		}
		printf("\n");
		
		unsigned char **test2 = ToSquareMatrix(test, cx2 - cx1, cy2 - cy1, 16);
		for(int y = 0; y < 16; y++)
		{
			for(int x = 0; x < 16; x++)
			{
				printf("%d ", test2[y][x]);
			}
			printf("\n");
		}
		printf("\n");
		
		for(int y = 0; y < 16; y++)
		{
			for(int x = 0; x < 16; x++)
			{
				printf("%d ", character.matrix[y][x]);
			}
			printf("\n");
		}
		printf("\n");

	}*/

	return character;
}

Text GetCharacters(Image image, Text text)
{
	for(int i = 0; i < text.numberOfParagraphs; i++)
	{
		for(int j = 0; j < text.paragraphs[i].numberOfLines; j++)
		{
			for(int k = 0; k < text.paragraphs[i].lines[j].numberOfWords; k++)
			{
				int characterId = 0;
				//printf("%d %d %d %d \n", i, j, k, characterId);

				// Prepare data
				Line line = text.paragraphs[i].lines[j];
				Word word = text.paragraphs[i].lines[j].words[k];
				Character *characters = (Character *)malloc(sizeof(Character) * 2 * word.numberOfCharacters);

				// Handle characters
				int cx1 = 0, cx2 = 0, cy1 = 0, cy2 = 0;
				int state = 0;
				for (int x = word.x1; x < word.x2; x++)
				{
					// Check for black pixels on vertical line x
					int y = line.y1, foundBlackPixel = 0, yMin = 0, yMax = 0;
					while (y < line.y2)
					{
						if (!foundBlackPixel && image.binarized[y][x] == 1)
						{
							yMin = y;
							foundBlackPixel = 1;
						}
						if (image.binarized[y][x] == 1)
						{
							yMax = y + 1;
						}
						y++;
					}

					if (foundBlackPixel)
					{
						if (state == 0)
						{
							cx1 = x;
							cy1 = yMin;
							cy2 = yMax;
							state = 1;
						}
						else
						{
							cx2 = x;
							if (yMin < cy1)
								cy1 = yMin;
							if (yMax > cy2)
								cy2 = yMax;
						}
					}
					else
					{
						if (state == 1 && x - cx2 > 4)
						{
							cx2 = x;
							/*if (cx2 - cx1 >= 2 * line.averageCharactersWidth)
							{
								int mid = (cx2 - cx1) / 2;
								characters[characterId] = __PrepareCharacter(cx1, cx1 + mid, cy1, cy2, image.binarized);
								characterId++;
								word.numberOfCharacters += 1;
								characters[characterId] = __PrepareCharacter(1 + cx1 + mid, cx2, cy1, cy2, image.binarized);
							}*/
							characters[characterId] = __PrepareCharacter(j, k, characterId, cx1, cx2, cy1, cy2, image.binarized);

							characterId++;
							state = 0;
						}
					}
				}

				// Update word
				text.paragraphs[i].lines[j].words[k].characters = characters;
			}
		}
	}

	return text;
}
