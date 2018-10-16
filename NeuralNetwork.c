#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define global values that represents our neural network. The names are explicit you should be able to understand to what each value correspond.

size_t numberInputNodes;
size_t numberHiddenNodes;
size_t numberOutputNodes;

double *biasHiddenLayer;
double *biasOutput;
double **weightInputToHidden;
double **weightHiddenToOutput;





// Define the functions that are going to be needed when calling Start to prevent compile errors and warnings.

double** ConstructMatrix(size_t line, size_t column);
double* ConstructArray(size_t size);





// Start is the function that initializes all the global values ~ thus, our neural network ~ , defined previously 
// according to the numbers of neurons in the Input Layer, in the Hidden Layer and in the Output Layer. 
// Then it fills all the matrices and arrays with random doubles between -1 and 1.

void Start(size_t inputNodes, size_t hiddenNodes, size_t outputNodes)
{
	numberInputNodes = inputNodes;
	numberHiddenNodes = hiddenNodes;
	numberOutputNodes = outputNodes;
	
	srand(time(NULL)); // seed the rand()

	biasHiddenLayer = ConstructArray(hiddenNodes); // construction of the array biasHiddenLayer, fill it with random values
        for (size_t i = 0; i < hiddenNodes; i++)
        {
                biasHiddenLayer[i] = (rand()/(double)RAND_MAX) * 2 - 1;
        }


	biasOutput = ConstructArray(outputNodes); // construction of the array biasOutput, fill it with random values
        for (size_t i = 0; i < outputNodes; i++)
        {
                biasOutput[i] = (rand()/(double)RAND_MAX) * 2 - 1;
        }
	

	weightInputToHidden = ConstructMatrix(inputNodes, hiddenNodes); // construction of the 2-dimensional matrix weigthInputToHidden, fill it with random values
	for (size_t j = 0; j < inputNodes; j++)
        {
                for (size_t k = 0; k < hiddenNodes; k++)
                        weightInputToHidden[j][k] = (rand()/(double)RAND_MAX) * 2 - 1;
        }

	
	weightHiddenToOutput = ConstructMatrix(hiddenNodes, outputNodes); // construction of the 2-dimensional matrix weigthHiddenToOutput, fill it with random values
	for (size_t j = 0; j < hiddenNodes; j++)
        {
                for (size_t k = 0; k < outputNodes; k++)
                        weightHiddenToOutput[j][k] = (rand()/(double)RAND_MAX) * 2 - 1;
        }
}
                                                                                




// This function creates and return a 2-dimensional matrix of size line * column, to do so it is going to return a **pointer.
// The dynamic allocation of the memory (malloc) permit to let the sizes of the matrix to determine at the moment of the compilation
// and create a matrix of the exact needed size.

double** ConstructMatrix(size_t line, size_t column) 
{
	double **matrix = (double **) malloc(sizeof(double *) * column);
	for (size_t i = 0; i < line; i++)
        {
                *(matrix + i) = (double *)malloc(sizeof(double) * column);
        }
	return matrix;
}




// This function creates and return a 1-dimensional matrix (an array) of size size, to do so it is going to return a *pointer.
// The dynamic allocation of the memory (malloc) permit to let the size of the matrix to determine at the moment of the compilation
// and create a matrix of the exact needed size.

double* ConstructArray(size_t size)
{
	double *array = (double *) malloc(sizeof(double) * size);
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





double* Predict(double inputs[])
{
	double *hiddenres = ConstructArray(numberHiddenNodes);
        for (size_t i = 0; i < numberHiddenNodes; i++)
                hiddenres[i] = 0;
        for (size_t j = 0; j < numberHiddenNodes; j++)
        {
                for (size_t i = 0; i < numberInputNodes; i++)
                        hiddenres[j] += inputs[i] * weightInputToHidden[i][j];
        }
        // bias et sigmoid
        
        double *output = ConstructArray(numberOutputNodes);
        for (size_t i = 0; i < numberOutputNodes; i++)
                output[i] = 0;
        for (size_t j = 0; j < numberOutputNodes; j++)
        {
                for (size_t i = 0; i < numberHiddenNodes; i++)
                        output[j] += hiddenres[i] * weightHiddenToOutput[i][j];
        }
        // bias et softmax

        return output;
}








//double* MultArrayMatrix(double arrayInput[], double matrixWeight[][])
//{
//        size_t lengthArrayInput = sizeof(arrayInput) / sizeof(arrayInput[0]);
//        size_t lengthMatrixWeight = sizeof(matrixWeight) / sizeof(matrixWeight[0][0]);
//        double* res = ConstructArray(lengthArrayInput, length);
//}






































