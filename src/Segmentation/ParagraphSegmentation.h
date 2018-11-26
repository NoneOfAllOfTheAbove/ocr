#ifndef PARAGRAPH_SEGMENTATION_H
#define PARAGRAPH_SEGMENTATION_H

int GetNumberHorizontalWhiteNeighbors(unsigned char**, int, int, int, int);
int GetNumberVerticalWhiteNeighbors(unsigned char**, int, int, int, int);
unsigned char **RLSA(unsigned char**, int, int);

Text GetParagraphs(Image, Text);

void __GetBoundsOfBlock(unsigned char**, int, int, int, int, int*, int*, int*, int*, int);
void __IdentifyBlocks(unsigned char**, int x, int y, int width, int height, int blockId);

#endif
