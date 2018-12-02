#include <stdio.h>
#include <stdlib.h>

#include "../Matrix.h"
#include "../Preprocessing/Preprocessing.h"
#include "Segmentation.h"

int __CountCharacters(unsigned char **matrix, int x1, int x2, int y1, int y2)
{
	int numberOfCharacters = 0;
	int state = 0;

	for (int x = x1; x < x2; x++)
	{
		int y = y1;
		while (y < y2 && matrix[y][x] != 1)
			y++;

		if (y != y2)
		{
			numberOfCharacters += (state == 0) ? 1 : 0;
			state = 1;
		}
		else
		{
			state = 0;
		}
	}

	return numberOfCharacters;
}

int __IdentifyCharacters(
	unsigned char **matrix,
	int x1, int x2, int y1, int y2,
	int *sumCharactersWidth
)
{
	int numberOfCharacters = 0;
	int state = 0;
	
	for(int x = x1; x < x2; x++)
	{
		int y = y1;
		while(y < y2 && matrix[y][x] != 1)
			y++;

		if(y != y2)
		{
			numberOfCharacters += (state == 0) ? 1 : 0;
			*sumCharactersWidth += 1;
			state = 1;
		}
		else
		{
			state = 0;
		}
	}

	return numberOfCharacters;
}

int __CountWords(
	unsigned char **matrix,
	int x1, int x2, int y1, int y2,
	int averageCharactersWidth
)
{
	int numberOfWords = 0;
	int spaceWidth = 0;
	int state = 0;

	for (int x = x1; x < x2; x++)
	{
		int y = y1;
		while (y < y2 && matrix[y][x] == 0)
			y++;

		if (y == y2)
		{
			if(state == 1)
			{
				spaceWidth++;
			}
		}
		else
		{
			state = 1;
			if(spaceWidth >= 1 + averageCharactersWidth / 2)
			{
				numberOfWords++;
			}
			spaceWidth = 0;
		}
	}

	return numberOfWords + 1;
}

Text GetWords(Image image, Text text)
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

			// Prepare data
			int sumCharactersWidth = 0;
			int numberOfCharacters = __IdentifyCharacters(
				image.binarized, x1, x2, y1, y2,
				&sumCharactersWidth
			);
			int averageCharactersWidth =
				sumCharactersWidth / numberOfCharacters;
			averageCharactersWidth =
				(averageCharactersWidth == 0) ? 1 : averageCharactersWidth;

			int numberOfWords = __CountWords(
				image.binarized, x1, x2, y1, y2,
				averageCharactersWidth
			);
			Word *words = (Word*)malloc(sizeof(Word) * numberOfWords);

			// Register words
			int wordId = 0;
			int startX = x1;
			int lastX = x1;
			int spaceWidth = 0;
			int state = 0;
			for (int x = x1; x < x2; x++)
			{
				int y = y1;
				while (y < y2 && image.binarized[y][x] == 0)
					y++;

				if (x == x2 - 1)
				{
					// printf("%d -> %d \n", startX, lastX + 1);
					Word word;
					word.x1 = startX;
					word.x2 = lastX + 2;
					word.numberOfCharacters = __CountCharacters(
						image.binarized,
						word.x1, word.x2, y1, y2
					);
					word.spaces = (x - word.x2) / averageCharactersWidth;
					words[wordId] = word;
					wordId++;
				}
				if (y == y2)
				{
					if(state == 1)
					{
						spaceWidth++;
					}
				}
				else
				{
					if(state == 0)
					{
						startX = x;
					}
					state = 1;
					if (spaceWidth >= 1 + averageCharactersWidth / 2)
					{
						// printf("%d -> %d \n", startX, lastX + 1);
						Word word;
						word.x1 = startX;
						word.x2 = lastX + 2;
						word.numberOfCharacters = __CountCharacters(
							image.binarized,
							word.x1,
							word.x2,
							y1,
							y2
						);
						word.spaces = (x - word.x2) / averageCharactersWidth;
						words[wordId] = word;
						wordId++;
						startX = x;
					}
					lastX = x;
					spaceWidth = 0;
				}
			}

			// Update line
			text.paragraphs[i].lines[j].averageCharactersWidth =
				averageCharactersWidth;
			text.paragraphs[i].lines[j].numberOfWords = numberOfWords;
			text.paragraphs[i].lines[j].words = words;
		}
	}

	return text;
}
