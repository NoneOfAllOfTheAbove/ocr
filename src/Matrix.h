#ifndef MATRIX_H
#define MATRIX_H

int **CreateIntMatrix(int width, int height);
unsigned char **CreateCharMatrix(int width, int height);
double **CreateDoubleMatrix(size_t line, size_t column);

void FreeMatrix(double**, size_t);

#endif