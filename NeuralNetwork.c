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


        /*// just to test
        printf ("\n\nhidden = \t");
        for (size_t i = 0; i < numberOutputNodes; i++)
        {
                printf("%f\n\t\t", hiddenRes[i]);
        }
        printf("\n");*/





        // get the result from the transition of Hidden to Output
        // layer by computing the weighted sum add the bias and apply
        // sigmoid to every element of output.

        double *outputs = ConstructArray(numberOutputNodes);

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

        /*double sumsoftmax = 0;
        for (size_t i = 0; i < numberOutputNodes; i++) with a 2 x 2 x 1 neural net, with a bias in the input and hidden layers, using the sigmoid activation funct
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
        printf ("\n\nprediction = \t");
        for (size_t i = 0; i < numberOutputNodes; i++)
        {
                printf("%f\n\t\t", outputs[i]);
        }
        printf("\n");

        return outputs; // matrix containing each output neuron's probability
}





// ---------------------------------Train--------------------------------------




void Train(double inputs[], double targets[])
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

        // hiddenRes is the output of the feedforwad between the input
        //layer and the hidden layer. It is also the input to the 
        //feedforward between hidden and output.

        double *outputs = ConstructArray(numberOutputNodes);
        //double sumsoftmax = 0;
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
        /**for (size_t i = 0; i < numberOutputNodes; i++)
                outputs[i] = exp(outputs[i]) / sumsoftmax;**/
        
        

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

        double learningRate = 0.1;

        //----------------------Hidden to Output---------------------------
        // calculate the error of the output layer
        double *errorOutput = ConstructArray(numberOutputNodes);
        for (size_t i = 0; i < numberOutputNodes; i++)
                errorOutput[i] = targets[i] - outputs[i];

        // calculate the gradient
        for (size_t i = 0; i < numberOutputNodes; i++)
        {
                outputs[i] = (outputs[i] * (1 - outputs[i])) * errorOutput[i] 
                * learningRate;
        }

        // Finally create the delta weight matrix
        // if error look here first ! (matrix dimension)
        double **deltaWeightHiddenToOutput = 
        ConstructMatrix(numberHiddenNodes, numberOutputNodes);

        for (size_t i = 0; i < numberHiddenNodes; i++)
        {
                for (size_t j = 0; j < numberOutputNodes; j++)
                        deltaWeightHiddenToOutput[i][j] = hiddenRes[i] * outputs[j];
        }

        // Add the deltaweight to the weight between the hidden layer and the output layer
        // and the outputs matrix to the bias of the ouputs matrix
        for (size_t i = 0; i < numberHiddenNodes; i++)
        {
                for (size_t j = 0; j < numberOutputNodes; j++)
                        weightHiddenToOutput[i][j] += deltaWeightHiddenToOutput[i][j];
        }
        for (size_t i = 0; i < numberOutputNodes; i++)
                biasOutput[i] += outputs[i];
        


        // ---------------------------Input to Hidden------------------------------------
        // calculate the error of the hidden layer which is the matrix product :
        // weight*errorOutput

        // LOOK HERE IF THERE ARE ERRORS
        double *errorHidden = ConstructArray(numberHiddenNodes);
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
                hiddenRes[i] = (hiddenRes[i] * (1 - hiddenRes[i])) * errorOutput[i]
                * learningRate;
        }

        // Finally create the deltaweight matrix
        double **deltaWeightInputToHidden = ConstructMatrix(numberInputNodes, numberHiddenNodes);

        for (size_t i = 0; i < numberInputNodes; i++)
        {
                for (size_t j = 0; j < numberHiddenNodes; j++)
                        deltaWeightInputToHidden[i][j] = inputs[i] * outputs[j];
        }

        // Add everything
        for (size_t i = 0; i < numberInputNodes; i++)
        {
                for (size_t j = 0; j < numberHiddenNodes; j++)
                        weightInputToHidden[i][j] += deltaWeightInputToHidden[i][j];
        }
        for (size_t i = 0; i < numberHiddenNodes; i++)
                biasHiddenLayer[i] += hiddenRes[i];
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
