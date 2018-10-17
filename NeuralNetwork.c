#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Define global values that represents our neural network. The names are
// explicit you should be able to understand to what each value correspond.

size_t numberInputNodes;
size_t numberHiddenNodes;
size_t numberOutputNodes;

double *biasHiddenLayer;
double *biasOutput;
double **weightInputToHidden;
double **weightHiddenToOutput;





// This function creates and return a 2-dimensional matrix of size
// line * column, to do so it is going to return a **pointer.
// The dynamic allocation of the memory (malloc) permit to let the sizes of
// the matrix to determine at the moment of the compilation and create a matrix
// of the exact needed size.

double** ConstructMatrix(size_t line, size_t column) 
{
	double **matrix = (double **) malloc(sizeof(double *) * column);
	for (size_t i = 0; i < line; i++)
        {
                *(matrix + i) = (double *)malloc(sizeof(double) * column);
        }
	return matrix;
}




// This function creates and return a 1-dimensional matrix (an array) of size
// size, to do so it is going to return a *pointer. The dynamic allocation of
// the memory (malloc) permit to let the size of the matrix to determine at 
// the moment of the compilation and create a matrix of the exact needed size.

double* ConstructArray(size_t size)
{
	double *array = (double *) malloc(sizeof(double) * size);
	return array;
}








// Start is the function that initializes all the global values ~ thus, our
// neural network ~ , defined previously according to the numbers of neurons
// in the Input Layer, in the Hidden Layer and in the Output Layer. Then it
// fills all the matrices and arrays with random doubles between -1 and 1.

void Start(size_t inputNodes, size_t hiddenNodes, size_t outputNodes)
{
	numberInputNodes = inputNodes;
	numberHiddenNodes = hiddenNodes;
	numberOutputNodes = outputNodes;
	
	srand(time(NULL)); // seed the rand()


        // construction of the array biasHiddenLayer, fill it with random values
	biasHiddenLayer = ConstructArray(hiddenNodes); 
        for (size_t i = 0; i < hiddenNodes; i++)
        {
                biasHiddenLayer[i] = (rand()/(double)RAND_MAX) * 2 - 1;
        }


        // construction of the array biasOutput, fill it with random values
	biasOutput = ConstructArray(outputNodes); 
        for (size_t i = 0; i < outputNodes; i++)
        {
                biasOutput[i] = (rand()/(double)RAND_MAX) * 2 - 1;
        }
	

        // construction of the 2-dimensional matrix weigthInputToHidden,
        // fill it with random values
	weightInputToHidden = ConstructMatrix(inputNodes, hiddenNodes); 
	for (size_t j = 0; j < inputNodes; j++)
        {
                for (size_t k = 0; k < hiddenNodes; k++)
                        weightInputToHidden[j][k] = (rand()/(double)RAND_MAX) * 2 - 1;
        }

	
        // construction of the 2-dimensional matrix weigthHiddenToOutput,
        // fill it with random values
	weightHiddenToOutput = ConstructMatrix(hiddenNodes, outputNodes); 
	for (size_t j = 0; j < hiddenNodes; j++)
        {
                for (size_t k = 0; k < outputNodes; k++)
                    
		        weightHiddenToOutput[j][k] = (rand()/(double)RAND_MAX) * 2 - 1;
        }
}
                                                                                



// --------------------------------Predict-------------------------------------




double* Predict(double inputs[])
{
        // get the result from the transition of Input to Hidden
        // layer by computing the weighted sum add the bias and apply
        // sigmoid to every element of hiddenres.

	double *hiddenRes = ConstructArray(numberHiddenNodes);
        for (size_t i = 0; i < numberHiddenNodes; i++)
                hiddenRes[i] = 0;
        for (size_t j = 0; j < numberHiddenNodes; j++)
        {
                for (size_t i = 0; i < numberInputNodes; i++)
                {
                        hiddenRes[j] += inputs[i] * weightInputToHidden[i][j];
                }
                hiddenRes[j] += biasHiddenLayer[j];
        }

        // Sigmoid
        for (size_t i = 0; i < numberHiddenNodes; i++)
                hiddenRes[i] = 1 / (1 + exp(-hiddenRes[i]));


        // just to test
        printf ("\n\nhidden = \t");
        for (size_t i = 0; i < numberOutputNodes; i++)
        {
                printf("%f\n\t\t", hiddenRes[i]);
        }
        printf("\n");





        // get the result from the transition of Hidden to Output
        // layer by computing the weighted sum add the bias and apply
        // sigmoid to every element of output.

        double *outputs = ConstructArray(numberOutputNodes);
        double sumsoftmax = 0;
        for (size_t i = 0; i < numberOutputNodes; i++)
                outputs[i] = 0;
        for (size_t j = 0; j < numberOutputNodes; j++)
        {
                for (size_t i = 0; i < numberHiddenNodes; i++)
                        outputs[j] += hiddenRes[i] * weightHiddenToOutput[i][j];
                outputs[j] += biasOutput[j];
                // Create the sum of exp(outputs[j]) needed for the softmax
                // activation function.
                sumsoftmax += exp(outputs[j]);
        }

        // softmax
        for (size_t i = 0; i < numberOutputNodes; i++)
                outputs[i] = exp(outputs[i]) / sumsoftmax;

        // just to test 
        printf ("\n\nprediction = \t");
        for (size_t i = 0; i < numberOutputNodes; i++)
        {
                printf("%f\n\t\t", outputs[i]);
        }
        printf("\n");

        return outputs; // matrix containing each output neuron's probability
}





















//-----------------------------------------------------------------------------

//-----If you want to print your global values decomment the part you need-----

void PrintGlobalValues()
{

        printf("\nnumberInputNodes = %ld\n", numberInputNodes);
        printf("\nnumberHiddenNodes = %ld\n", numberHiddenNodes);
        printf("\nnumberOutputNodes = %ld\n", numberOutputNodes);


	printf ("\n\nweightInputToHidden = \t");
        for (size_t i = 0; i < numberInputNodes; i++)
        {
                for (size_t j = 0; j < numberHiddenNodes; j++)
                {
                        printf("%f      ", weightInputToHidden[i][j]);
                }
                printf("\n\t\t\t");
        }

        printf ("\n\nweightHiddenToOutput = \t");
        for (size_t i = 0; i < numberHiddenNodes; i++)
        {
                for (size_t j = 0; j < numberOutputNodes; j++)
                {
                        printf("%f      ", weightHiddenToOutput[i][j]);
                }
                printf("\n\t\t\t");
        }

        printf ("\n\nbiasHiddenLayer = \t");
        for (size_t i = 0; i < numberHiddenNodes; i++)
        {
                printf("%f\n\t\t\t", biasHiddenLayer[i]);
        }

        printf ("\n\nbiasOutput = \t");
        for (size_t i = 0; i < numberOutputNodes; i++)
        {
                printf("%f\n\t\t", biasOutput[i]);
        }
        printf("\n");

}






















