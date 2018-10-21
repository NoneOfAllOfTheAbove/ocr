#ifndef SEGMENTATION_H
#define  SEGMENTATION_H

typedef struct {
 unsigned char *array;
 size_t used;
 size_t size;
} Array ;

int **BuildMatrix(size_t line, size_t column);
unsigned char *Bloc_Detection(unsigned char **matrix);
unsigned char *Labelling_GetCharacters();
unsigned char *Labelling(unsigned char **matrix, int width, int height);
unsigned char *Line_Detection(unsigned char **matrix, unsigned char *xblocs);
unsigned char *Bloc_Line_Detection(unsigned char **matrix);
void CheckNeighbours(int x, int y);
void freeArray(Array *a);
void initArray(Array *a, size_t initialSize);
void insertArray(Array *a, unsigned char element);
void Labelling_FirstPass(unsigned char **matrix);
void Labelling_SecondPass();

#endif
