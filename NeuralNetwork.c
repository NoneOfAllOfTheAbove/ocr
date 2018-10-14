#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define global values that represents our neural network. The names are explicit you should be able to understand to what each value correspond.

int numberInputNodes;
int numberHiddenNodes;
int numberOutputNodes;

double *biasHiddenLayer;
double *biasOutput;
double **weightInputToHidden;
double **weightHiddenToOutput;





// Define the functions that are going to be needed when calling Start to prevent compile errors and warnings.

double** ConstructMatrix(int line, int column);
double* ConstructArray(int size);





// Start is the function that initializes all the global values ~ thus, our neural network ~ , defined previously 
// according to the numbers of neurons in the Input Layer, in the Hidden Layer and in the Output Layer. 
// Then it fills all the matrices and arrays with random doubles between -1 and 1.

void Start(int inputNodes, int hiddenNodes, int outputNodes)
{
	numberInputNodes = inputNodes;
	numberHiddenNodes = hiddenNodes;
	numberOutputNodes = outputNodes;
	
	srand(time(NULL)); // seed the rand()

	biasHiddenLayer = ConstructArray(hiddenNodes); // construction of the array biasHiddenLayer, fill it with random values
        for (int i = 0; i < hiddenNodes; i++)
        {
                biasHiddenLayer[i] = (rand()/(double)RAND_MAX) * 2 - 1;
        }


	biasOutput = ConstructArray(outputNodes); // construction of the array biasOutput, fill it with random values
        for (int i = 0; i < outputNodes; i++)
        {
                biasOutput[i] = (rand()/(double)RAND_MAX) * 2 - 1;
        }
	

	weightInputToHidden = ConstructMatrix(inputNodes, hiddenNodes); // construction of the 2-dimensional matrix weigthInputToHidden, fill it with random values
	for (int j = 0; j < inputNodes; j++)
        {
                for (int k = 0; k < hiddenNodes; k++)
                        weightInputToHidden[j][k] = (rand()/(double)RAND_MAX) * 2 - 1;
        }

	
	weightHiddenToOutput = ConstructMatrix(hiddenNodes, outputNodes); // construction of the 2-dimensional matrix weigthHiddenToOutput, fill it with random values
	for (int j = 0; j < hiddenNodes; j++)
        {
                for (int k = 0; k < outputNodes; k++)
                        weightHiddenToOutput[j][k] = (rand()/(double)RAND_MAX) * 2 - 1;
        }
}





// This function creates and return a 2-dimensional matrix of size line * column, to do so it is going to return a **pointer.
// The dynamic allocation of the memory (malloc) permit to let the sizes of the matrix to determine at the moment of the compilation
// and create a matrix of the exact needed size.
//
// Todo: try to fill the matrix with random double here to make Start more readable and beautiful.

double** ConstructMatrix(int line, int column) 
{
	double **matrix = (double **) malloc(sizeof(double *) * column);
	for (int i = 0; i < line; i++)
        {
                *(matrix + i) = (double *)malloc(sizeof(double) * column);
        }
	
//	srand(time(NULL));
//	for (int j = 0; j < line; j++)
//	{
//		for (int k = 0; k < column; k++)
//			matrix[j][k] = (rand()/(double)RAND_MAX) * 2 - 1;
//	}
	
	return matrix;
}




// This function creates and return a 1-dimensional matrix (an array) of size size, to do so it is going to return a *pointer.
// The dynamic allocation of the memory (malloc) permit to let the size of the matrix to determine at the moment of the compilation
// and create a matrix of the exact needed size.
//
// Todo: try to fill the array with random double here to make Start more readable and beautiful.

double* ConstructArray(int size)
{
	double *array = (double *) malloc(sizeof(double) * size);
	
	//srand(time(NULL));
//	for (int i = 0; i < size; i++)
//	{
//		array[i] = (rand()/(double)RAND_MAX) * 2 - 1;
//	}

	return array;
}






//  ------------------------------------------- if you want to print your global values decomment the part you need --------------------------------------------------

void PrintGlobalValues()
{
/*
        printf("\nnumberInputNodes = %d\n", numberInputNodes);
        printf("\nnumberHiddenNodes = %d\n", numberHiddenNodes);
        printf("\nnumberOutputNodes = %d\n", numberOutputNodes);


	printf ("\n\nweightInputToHidden = \t");
        for (int i = 0; i < numberInputNodes; i++)
        {
                for (int j = 0; j < numberHiddenNodes; j++)
                {
                        printf("%f      ", weightInputToHidden[i][j]);
                }
                printf("\n\t\t\t");
        }

        printf ("\n\nweightHiddenToOutput = \t");
        for (int i = 0; i < numberHiddenNodes; i++)
        {
                for (int j = 0; j < numberOutputNodes; j++)
                {
                        printf("%f      ", weightHiddenToOutput[i][j]);
                }
                printf("\n\t\t\t");
        }

        printf ("\n\nbiasHiddenLayer = \t");
        for (int i = 0; i < numberHiddenNodes; i++)
        {
                printf("%f\n\t\t\t", biasHiddenLayer[i]);
        }

        printf ("\n\nbiasOutput = \t");
        for (int i = 0; i < numberOutputNodes; i++)
        {
                printf("%f\n\t\t", biasOutput[i]);
        }
        printf("\n");
*/
}

