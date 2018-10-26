#ifndef BLOCKDETECTION_H
#define BLOCKDETECTION_H

int GetNumberHorizontalWhiteNeighbors(unsigned char**, int, int, int, int);
int GetNumberVerticalWhiteNeighbors(unsigned char**, int, int, int, int);
unsigned char **RLSA(unsigned char**, int, int);

int **IdentifyBlocks(unsigned char**, int*, int, int);
void __IdentifyBlocks(unsigned char**, int, int, int, int, int*, int*, int*, int*, int);

int** DetectBlocks(unsigned char**, int*, int, int);

#endif