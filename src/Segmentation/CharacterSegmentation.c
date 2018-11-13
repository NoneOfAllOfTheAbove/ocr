#include <stdio.h>
#include <stdlib.h>

#include "../Matrix.h"
#include "../Preprocessing/Preprocessing.h"
#include "Segmentation.h"
#include "WordSegmentation.h"

Character __PrepareCharacter(int cx1, int cx2, int cy1, int cy2, unsigned char **matrix)
{
	Character character;
	character.x1 = cx1;
	character.x2 = cx2;
	character.y1 = cy1;
	character.y2 = cy2;
	character.character = '\0';
	character.matrix = GetSubMatrix(matrix, cx1, cy1, cx2, cy2);
	character.matrix = ToSquareMatrix(character.matrix, cx2 - cx1, cy2 - cy1, 16);
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
				// Prepare data
				Line line = text.paragraphs[i].lines[j];
				Word word = text.paragraphs[i].lines[j].words[k];
				Character *characters = (Character *)malloc(sizeof(Character) * 2 * word.numberOfCharacters);

				// Handle characters
				int cx1 = 0, cx2 = 0, cy1 = 0, cy2 = 0;
				int characterId = 0, state = 0;
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
							if (yMin < cy1)
								cy1 = yMin;
							if (yMax > cy2)
								cy2 = yMax;
						}
					}
					else
					{
						if (state == 1)
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
							characters[characterId] = __PrepareCharacter(cx1, cx2, cy1, cy2, image.binarized);

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
