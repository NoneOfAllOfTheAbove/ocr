#include <stdio.h>

#include "../Preprocessing/Preprocessing.h"

#include "Segmentation.h"
#include "ParagraphSegmentation.h"
#include "LineSegmentation.h"
#include "WordSegmentation.h"
#include "CharacterSegmentation.h"

/*void PrintCharacter(Character c)
{
	for(int a = 0; a < 16; a++)
	{
		for(int b = 0; b < 16; b++)
		{
			if(c.matrix[a][b] > 0)
			{
				printf("%d ", c.matrix[a][b]);
			} else
			{
				if((a == 0) || (b == 0) || a == 15 || b == 15)
				{
					printf("- ");
				}
				else
				{
					printf("  ");
				}
			}
		}
		printf("\n");
	}
}

void PrintLine(Line l)
{
	for(int w = 0; w < l.numberOfWords; w++)
	{
		for(int c = 0; c < l.words[w].numberOfCharacters; c++)
		{
			PrintCharacter(l.words[w].characters[c]);
			printf("\n");
		}
		printf("%d spaces \n", l.words[w].spaces);
	}
}

void DebugSegmentation(Text text)
{
	printf("Text (%d paragraphs)\n\n", text.numberOfParagraphs);
	for(int i = 0; i < text.numberOfParagraphs; i++)
	{
		printf(
			"\t Paragraph %d (%d lines)\n\n",
			i,
			text.paragraphs[i].numberOfLines
		);
		for(int j = 0; j < text.paragraphs[i].numberOfLines; j++)
		{
			printf(
				"\t\t Line %d (%d characters) \n",
				j,
				text.paragraphs[i].lines[j].numberOfCharacters
			);
			PrintLine(text.paragraphs[i].lines[j]);
			printf("\n\n");
		}
	}
}*/

Text Segmentation(Image image)
{
	Paragraph p[0];
	Text text;
	text.numberOfParagraphs = 0;
	text.paragraphs = p;

	text = GetParagraphs(image, text);
	text = GetLines(image, text);
	text = GetWords(image, text);
	text = GetCharacters(image, text);
	
	return text;
}
