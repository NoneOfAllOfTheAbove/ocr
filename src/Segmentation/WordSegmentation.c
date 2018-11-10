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

			// Count words
			int sumCharactersWidth = 0;
			int numberOfCharacters = __CountCharacters(image.binarized, x1, x2, y1, y2, &sumCharactersWidth);
			int numberOfWords = 0;
			int spaceWidth = 0;
			for(int x = x1; x < x2; x++)
			{
				int y = y1;
				while(y < y2 && image.binarized[y][x] == 0)
				{
					y++;
				}
				if(y == y2)
				{
					if(spaceWidth != 0)
					{
						spaceWidth++;
					}
				}
				else
				{
					if(spaceWidth > sumCharactersWidth / numberOfCharacters)
					{
						numberOfWords++;
					}
					spaceWidth = 0;
				}
			}
			Word *words = (Word*)malloc(sizeof(Word) * numberOfWords);


			// Register words
			int xStart = 0, state = 0, xEnd = 0, wordId = 0;
			for(int x = x1; x < x2; x++)
			{
				int y = y1;
				while(y < y2 && image.binarized[y][x] == 0)
				{
					y++;
				}
				if(y == y2)
				{
					if(state == 0)
					{
						xStart = x;
						state = 1;
					}
				}
				else
				{
					if(state == 1 && xEnd - xStart >= sumCharactersWidth / numberOfCharacters)
					{
						xEnd = x;

						Word word;
						word.x1 = xStart;
						word.x2 = xEnd;
						words[wordId] = word;
					}
					state = 0;
				}
			}

			// Update line
			text.paragraphs[i].lines[j].numberOfWords = numberOfWords;
			text.paragraphs[i].lines[j].words = words;
		}
	}

	return text;
}
