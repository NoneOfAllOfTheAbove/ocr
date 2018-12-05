#ifndef SEGMENTATION_H
#define SEGMENTATION_H

typedef struct Character Character;
struct Character
{
	int x1;
	int x2;
	int y1;
	int y2;
	
	unsigned char **matrix;

	char character;
};

typedef struct Word Word;
struct Word
{
	int x1;
	int x2;

	int spaces;

	int numberOfCharacters;
	Character* characters;
};

typedef struct Line Line;
struct Line
{
	int y1;
	int y2;

	int averageCharactersWidth;
	
	int numberOfWords;
	Word* words;
};

typedef struct Paragraph Paragraph;
struct Paragraph
{
	int x;
	int y;
	int width;
	int height;

	int numberOfLines;
	Line *lines;
};

typedef struct Text Text;
struct Text
{
	unsigned char **blocksMap;

	int deskewX1;
	int deskewX2;
	int deskewY1;
	int deskewY2;

	int numberOfParagraphs;
	Paragraph *paragraphs;
};

Text Segmentation(Image);

#endif
