#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "../Matrix.h"

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

// placed in Matrix.c now

// This function creates and return a 1-dimensional matrix (an array) of size
// size, to do so it is going to return a *pointer. The dynamic allocation of
// the memory (malloc) permit to let the size of the matrix to determine at
// the moment of the compilation and create a matrix of the exact needed size.

double* CreateArray(size_t size)
{
	double *array = (double *)malloc(sizeof(double) * size);
	if (array == NULL)
		exit(0);
	return array;
}


// ----------------------------------Start----------------------------------

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
	biasHiddenLayer = CreateArray(hiddenNodes);
	for (size_t i = 0; i < hiddenNodes; i++)
	{
		biasHiddenLayer[i] = (rand() / (double)RAND_MAX) * 2 - 1;
	}

	// construction of the array biasOutput, fill it with random values
	biasOutput = CreateArray(outputNodes);
	for (size_t i = 0; i < outputNodes; i++)
	{
		biasOutput[i] = (rand() / (double)RAND_MAX) * 2 - 1;
	}

	// construction of the 2-dimensional matrix weigthInputToHidden,
	// fill it with random values
	weightInputToHidden = CreateDoubleMatrix(inputNodes, hiddenNodes);
	for (size_t j = 0; j < inputNodes; j++)
	{
		for (size_t k = 0; k < hiddenNodes; k++)
			weightInputToHidden[j][k] = (rand() / (double)RAND_MAX) * 2 - 1;
	}

	// construction of the 2-dimensional matrix weigthHiddenToOutput,
	// fill it with random values
	weightHiddenToOutput = CreateDoubleMatrix(hiddenNodes, outputNodes);
	for (size_t j = 0; j < hiddenNodes; j++)
	{
		for (size_t k = 0; k < outputNodes; k++)

			weightHiddenToOutput[j][k] = (rand() / (double)RAND_MAX) * 2 - 1;
	}
}

// --------------------------------Predict-------------------------------------

double* Predict(double inputs[])
{
	// get the result from the transition of Input to Hidden
	// layer by computing the weighted sum add the bias and apply
	// sigmoid to every element of hiddenres.

	double *hiddenRes = CreateArray(numberHiddenNodes);
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

	/*// just to test
		printf ("\n\nhidden = \t");
		for (size_t i = 0; i < numberOutputNodes; i++)
		{
				printf("%f\n\t\t", hiddenRes[i]);
		}
		printf("\n");*/

	// get the result from the transition of Hidden to Output
	// layer by computing the weighted sum add the bias and apply
	// sigmoid to every element of output. CCC

	double *outputs = CreateArray(numberOutputNodes);

	for (size_t i = 0; i < numberOutputNodes; i++)
		outputs[i] = 0;
	for (size_t j = 0; j < numberOutputNodes; j++)
	{
		for (size_t i = 0; i < numberHiddenNodes; i++)
		{
			outputs[j] += hiddenRes[i] * weightHiddenToOutput[i][j];
		}
		outputs[j] += biasOutput[j];
	}

	// Sigmoid CCC
	for (size_t i = 0; i < numberOutputNodes; i++)
		outputs[i] = 1 / (1 + exp(-outputs[i]));

	/*double sumsoftmax = 0;
		for (size_t i = 0; i < numberOutputNodes; i++)
		with a 2 x 2 x 1 neural net, with a bias 
		 in the input and hidden layers, using the sigmoid activation funct
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
				outputs[i] = exp(outputs[i]) / sumsoftmax;*/

	// just to test
	//printf("prediction = \t");
    /*
	for (size_t i = 0; i < numberOutputNodes; i++)
	{
		printf("%f\n\t\t", outputs[i]);
	}
	printf("\n");*/

	free(hiddenRes);

	return outputs; // matrix containing each output neuron's probability
}

// ---------------------------------Train--------------------------------------

void Train(double inputs[], double targets[])
{
	// get the result from the transition of Input to Hidden
	// layer by computing the weighted sum add the bias and apply
	// sigmoid to every element of hiddenres.

	double *hiddenRes = CreateArray(numberHiddenNodes);
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

	// hiddenRes is the output of the feedforwad between the input
	//layer and the hidden layer. It is also the input to the
	//feedforward between hidden and output.

	double *outputs = CreateArray(numberOutputNodes);
	//double sumsoftmax = 0;
	/*
		for (size_t i = 0; i < numberOutputNodes; i++)
				outputs[i] = 0;
		for (size_t j = 0; j < numberOutputNodes; j++)
		{
			for (size_t i = 0; i < numberHiddenNodes; i++)
					outputs[j] += hiddenRes[i] * weightHiddenToOutput[i][j];
			outputs[j] += biasOutput[j];
			// Create the sum of exp(outputs[j]) needed for the softmax
			// activation function.
			//sumsoftmax += exp(outputs[j]);
		}

		// softmax
		for (size_t i = 0; i < numberOutputNodes; i++)
				outputs[i] = exp(outputs[i]) / sumsoftmax;

		*/

	for (size_t i = 0; i < numberOutputNodes; i++)
		outputs[i] = 0;
	for (size_t j = 0; j < numberOutputNodes; j++)
	{
		for (size_t i = 0; i < numberHiddenNodes; i++)
		{
			outputs[j] += hiddenRes[i] * weightHiddenToOutput[i][j];
		}
		outputs[j] += biasOutput[j];
	}

	// Sigmoid
	for (size_t i = 0; i < numberOutputNodes; i++)
		outputs[i] = 1 / (1 + exp(-outputs[i]));

	double learningRate = 0.5;

	//----------------------Output to Hidden---------------------------
	// calculate the error of the output layer
	double *errorOutput = CreateArray(numberOutputNodes);
	for (size_t i = 0; i < numberOutputNodes; i++)
		errorOutput[i] = targets[i] - outputs[i];

	// calculate the gradient
	for (size_t i = 0; i < numberOutputNodes; i++)
	{
		outputs[i] =
			(outputs[i] * (1 - outputs[i])) * errorOutput[i] * learningRate;
	}

	// Finally create the delta weight matrix
	// if error look here first ! (matrix dimension)
	double **deltaWeightHiddenToOutput =
		CreateDoubleMatrix(numberHiddenNodes, numberOutputNodes);

	for (size_t i = 0; i < numberHiddenNodes; i++)
	{
		for (size_t j = 0; j < numberOutputNodes; j++)
			deltaWeightHiddenToOutput[i][j] = hiddenRes[i] * outputs[j];
	}

	// Add the deltaweight to the weights between the hidden layer
	// and the output layer and the outputs matrix to the bias of
	// the ouputs matrix  ccc
	for (size_t i = 0; i < numberHiddenNodes; i++)
	{
		for (size_t j = 0; j < numberOutputNodes; j++)
			weightHiddenToOutput[i][j] += deltaWeightHiddenToOutput[i][j];
	}
	for (size_t i = 0; i < numberOutputNodes; i++)
		biasOutput[i] += outputs[i];

	// ---------------------------Hidden to Input------------------------------
	// calculate the error of the hidden layer which is the matrix product :
	// weight*errorOutput

	// LOOK HERE IF THERE ARE ERRORS
	double *errorHidden = CreateArray(numberHiddenNodes);
	for (size_t i = 0; i < numberHiddenNodes; i++)
		errorHidden[i] = 0;

	for (size_t i = 0; i < numberHiddenNodes; i++)
	{
		for (size_t j = 0; j < numberOutputNodes; j++)
			errorHidden[i] += errorOutput[j] * weightHiddenToOutput[i][j];
	}

	// Calculate the gradient
	for (size_t i = 0; i < numberHiddenNodes; i++)
	{
		hiddenRes[i] = (hiddenRes[i] * (1 - hiddenRes[i])) *
			errorHidden[i] * learningRate;
	}

	// Finally create the deltaweight matrix
	double **deltaWeightInputToHidden = CreateDoubleMatrix(
		numberInputNodes,
		numberHiddenNodes
	);

	for (size_t i = 0; i < numberInputNodes; i++)
	{
		for (size_t j = 0; j < numberHiddenNodes; j++)
			deltaWeightInputToHidden[i][j] = inputs[i] * hiddenRes[j];
	}

	// Add everything
	for (size_t i = 0; i < numberInputNodes; i++)
	{
		for (size_t j = 0; j < numberHiddenNodes; j++)
			weightInputToHidden[i][j] += deltaWeightInputToHidden[i][j];
	}
	for (size_t i = 0; i < numberHiddenNodes; i++)
		biasHiddenLayer[i] += hiddenRes[i];

	FreeMatrix(deltaWeightHiddenToOutput, numberHiddenNodes);
	FreeMatrix(deltaWeightInputToHidden, numberInputNodes);
	free(hiddenRes);
	free(outputs);
	free(errorOutput);
	free(errorHidden);
}

//-----------------------------------------------------------------------------

//-----If you want to print your global values decomment the part you need-----

void PrintGlobalValues()
{

	printf("\nnumberInputNodes = %ld\n", numberInputNodes);
	printf("\nnumberHiddenNodes = %ld\n", numberHiddenNodes);
	printf("\nnumberOutputNodes = %ld\n", numberOutputNodes);

	printf("\n\nweightInputToHidden = \t");
	for (size_t i = 0; i < numberInputNodes; i++)
	{
		for (size_t j = 0; j < numberHiddenNodes; j++)
		{
			printf("%f\t", weightInputToHidden[i][j]);
		}
		printf("\n\t\t\t");
	}

	printf("\n\nweightHiddenToOutput = \t");
	for (size_t i = 0; i < numberHiddenNodes; i++)
	{
		for (size_t j = 0; j < numberOutputNodes; j++)
		{
			printf("%f\t", weightHiddenToOutput[i][j]);
		}
		printf("\n\t\t\t");
	}

	printf("\n\nbiasHiddenLayer = \t");
	for (size_t i = 0; i < numberHiddenNodes; i++)
	{
		printf("%f\n\t\t\t", biasHiddenLayer[i]);
	}

	printf("\n\nbiasOutput = \t");
	for (size_t i = 0; i < numberOutputNodes; i++)
	{
		printf("%f\n\t\t", biasOutput[i]);
	}
	printf("\n");
}

// ***
//
// SAVE AND LOAD
//
// ***

void Load(char *path)
{
	FILE *f = fopen(path, "r");

	// Count number of lines in file
	int numberLines = 0;
	char str[1000];
	while (fgets(str, 1000, f) != NULL)
	{
		numberLines++;
	}

	// Make an array of the value (a double) of each line
	double lines[numberLines];
	size_t currentLineNumber = 0;
	rewind(f);
	while (fgets(str, 1000, f) != NULL)
	{
		if (
			str[0] != '#' && str[0] != '\n' && str[0] != ' ' &&
			str[0] != '\0' && (int)str[0] != 13
		)
		{
			double a;
			sscanf(str, "%le", &a);
			lines[currentLineNumber] = a;

			//printf("%ld : %f\n", currentLineNumber, a);

			currentLineNumber++;
		}
	}

	/*for (int i = 0; i < numberLines; i++)
	{
		printf("%d : %f \n", i, lines[i]);
	}*/

	// Load values of lines in global values

	numberInputNodes = lines[0];
	numberHiddenNodes = lines[1];
	numberOutputNodes = lines[2];
	currentLineNumber = 3;

	// biasHiddenLayer
	for (size_t i = 0; i < numberHiddenNodes; i++)
	{
		biasHiddenLayer[i] = lines[currentLineNumber];
		currentLineNumber++;
	}

	// biasOutput
	for (size_t i = 0; i < numberOutputNodes; i++)
	{
		biasOutput[i] = lines[currentLineNumber];
		currentLineNumber++;
	}

	// weightInputToHidden
	for (size_t i = 0; i < numberInputNodes; i++)
	{
		for (size_t j = 0; j < numberHiddenNodes; j++)
		{
			weightInputToHidden[i][j] = lines[currentLineNumber];
			currentLineNumber++;
		}
	}

	// weightHiddenToOutput
	for (size_t i = 0; i < numberHiddenNodes; i++)
	{
		for (size_t j = 0; j < numberOutputNodes; j++)
		{
			weightHiddenToOutput[i][j] = lines[currentLineNumber];
			currentLineNumber++;
		}
	}

	fclose(f);
}

void Save(char *path)
{
	FILE *f = fopen(path, "w");
	fprintf(f, "# NEURAL NETWORK DATA\n\n");

	// Write NN's structure
	fprintf(f, "# Structure\n");
	fprintf(f, "%zu\n", numberInputNodes);
	fprintf(f, "%zu\n", numberHiddenNodes);
	fprintf(f, "%zu\n\n", numberOutputNodes);

	// biasHiddenLayer
	fprintf(f, "# biasHiddenLayer\n");
	for (size_t i = 0; i < numberHiddenNodes; i++)
	{
		fprintf(f, "%f\n", biasHiddenLayer[i]);
	}

	// biasOutput
	fprintf(f, "\n# biasOutput\n");
	for (size_t j = 0; j < numberOutputNodes; j++)
	{
		fprintf(f, "%f\n", biasOutput[j]);
	}

	// weightInputToHidden
	fprintf(f, "\n# weightInputToHidden\n");
	for (size_t i = 0; i < numberInputNodes; i++)
	{
		for (size_t j = 0; j < numberHiddenNodes; j++)
		{
			fprintf(f, "%f\n", weightInputToHidden[i][j]);
		}
	}

	// weightHiddenToOutput
	fprintf(f, "\n# weightHiddenToOutput\n");
	for (size_t i = 0; i < numberHiddenNodes; i++)
	{
		for (size_t j = 0; j < numberOutputNodes; j++)
		{
			fprintf(f, "%f\n", weightHiddenToOutput[i][j]);
		}
	}

	fclose(f);
}
