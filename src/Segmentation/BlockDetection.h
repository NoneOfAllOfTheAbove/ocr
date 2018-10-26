#ifndef BLOCKDETECTION_H
#define  BLOCKDETECTION_H

unsigned char** DetectBlocks(unsigned char**, int, int);
void Labeling(unsigned char **matrix, int x, int y, int width, int height, int*, int*, int);
int **GetBlocks(unsigned char** matrix, int imageWidth, int imageHeight);
int **GetLines(unsigned char **matrix, int **blocks, int imageWidth, int imageHeight);

#endif