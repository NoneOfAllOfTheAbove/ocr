#ifndef MATRIX_H
#define MATRIX_H

unsigned char **CreateCharMatrix(int width, int height);
double **CreateDoubleMatrix(size_t line, size_t column);

void FreeMatrix(double**, size_t);
void DestroyCharMatrix(unsigned char **matrix, int lines);

unsigned char **GetSubMatrix(
	unsigned char **matrix,
	int x1,
	int y1,
	int x2,
	int y2
);
unsigned char **ToSquareMatrix(
	unsigned char **matrix,
	int oldX,
	int oldY,
	int
);

void SaveMatrixAsImage(
	unsigned char **matrix,
	int width,
	int height,
	char *path
);

#endif
