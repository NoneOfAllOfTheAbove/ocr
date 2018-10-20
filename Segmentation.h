#ifndef SEGMENTATION_H
#define  SEGMENTATION_H

void CheckNeighbours(int x, int y, double **matrix);
double** ConstructMatrix(size_t line, size_t column);
void freeArray(Array *a);
void initArray(Array *a, size_t initialSize);
void insertArray(Array *a, double element);
void Labelling_FirstPass(double **matrix);
Array Labelling_GetCharacters();
void Labelling_SecondPass();
Array Labelling(double **matrix);

#endif
