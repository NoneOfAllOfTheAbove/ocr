#include <stdio.h>

#include "../Preprocessing/Preprocessing.h"

#include "Segmentation.h"
#include "ParagraphSegmentation.h"
#include "LineSegmentation.h"
#include "CharacterSegmentation.h"

void DebugSegmentation(Text text)
{
	/*printf("Text (%d paragraphs)\n\n", text.numberOfParagraphs);
	for(int i = 0; i < text.numberOfParagraphs; i++)
	{
		printf("\t Paragraph %d (%d lines)\n\n", i, text.paragraphs[i].numberOfLines);
		for(int j = 0; j < text.paragraphs[i].numberOfLines; j++)
		{
			printf("\t\t Line %d (%d characters) \n", j, text.paragraphs[i].lines[j].numberOfCharacters);
			for(int c = 0; c < text.paragraphs[i].lines[j].numberOfCharacters; c++)
			{
				for(int a = 0; a < 16; a++)
				{
					for(int b = 0; b < 16; b++)
					{
						if(text.paragraphs[i].lines[j].characters[c].matrix[a][b] == 1)
						{
							printf("%d ", text.paragraphs[i].lines[j].characters[c].matrix[a][b]);
						} else
						{
							printf("  ");
						}
					}
					printf("\n");
				}
				printf("\n");
			}
			printf("\n\n");
		}
		printf("\n\n");
	}*/

	/*int i = 1;
	int j = 1;
	for(int c = 0; c < text.paragraphs[i].lines[j].numberOfCharacters - 4; c++)
	{
		for(int a = 0; a < 16; a++)
		{
			for(int b = 0; b < 16; b++)
			{
				if(text.paragraphs[i].lines[j].characters[c].matrix[a][b] == 1)
				{
					printf("%d ", text.paragraphs[i].lines[j].characters[c].matrix[a][b]);
				} else
				{
					printf("  ");
				}
			}
			printf("\n");
		}
		printf("\n");
	}*/

}

Text Segmentation(Image image)
{
	Paragraph p[0];
	Text text;
	text.numberOfParagraphs = 0;
	text.paragraphs = p;

	text = GetParagraphs(image, text);	
	text = GetLines(image, text);
	text = GetCharacters(image, text);
	
	DebugSegmentation(text);
	return text;
}
