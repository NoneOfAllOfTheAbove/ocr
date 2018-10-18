#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// just for tests
#include <time.h>

#include "NeuralNetwork.h"
#include "Image.h"


int main()
{
	// ----------------------------------------
	// STEP 1 : IMAGE LOADING AND PREPROCESSING
	// ----------------------------------------

	// Load image
	SDL_Surface *imageSurface;
	char imagePath[] = "test.bmp";
	int imageWidth, imageHeight;
	LoadImage(&imageSurface, imagePath, &imageWidth, &imageHeight);

	// Create the matrix (height * width, representing grayscale of the image, each value is a double between 0 and 1)
	double **matrix = (double **) malloc(sizeof(double *) * imageHeight);
	for (int i = 0; i < imageWidth; i++)
	{
		*(matrix + i) = (double *)malloc(sizeof(double) * imageHeight);
	}
	ImageToMatrix(imageSurface, matrix);

	// -----------------------------
	// STEP 2 : CHARACTERS DETECTION
	// -----------------------------

	// -------------------------------
	// STEP 3 : CHARACTERS RECOGNITION
	// -------------------------------

	double input1[] = {1, 0};
	double output1[] = {1};

	double input2[] = {0, 1};
	double output2[] = {1};
	
	double input3[] = {1, 1};
	double output3[] = {0};

	double input4[] = {0, 0};
	double output4[] = {0};

	Start(2, 2, 1);
	PrintGlobalValues();
	Predict(input1);
	Predict(input1);
	Predict(input2);
	Predict(input3);
	Predict(input4);

	//printf("\n\n----------------------------------------------------------\n\n");

	srand(time(NULL));
	long t;
	for (int i = 0; i < 50; i++)
	{
		t = rand() % 4;
		printf("%ld \n", t);
		if (t == 0)
		{
			Train(input1, output1);
		}
		if (t == 1)
		{
			Train(input2, output2);
		}
		if (t == 3)
		{
			Train(input3, output3);
		}
		else
		{
			Train(input4, output4);
		}
	}


	
	PrintGlobalValues();
	Predict(input1);
	Predict(input2);
	Predict(input3);
	Predict(input4);




/*	double a[] = {4, 5, 6};
	double **b = ConstructMatrix(3, 3);
	int k = 1;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{	b[i][j] = k;
			k += 1;
		}
	}

	printf ("\n\na = \t");
	for (int i = 0; i < 3; i++)
	{
			printf("%f\n\t", a[i]);
	}
	printf("\n");

printf ("\n\nb = \t");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%f      ", b[i][j]);
		}
		printf("\n\t");
	}
	

	double *output = ConstructArray(3);
        for (size_t i = 0; i < 3; i++)
                output[i] = 0;
        for (size_t j = 0; j < 3; j++)
        {
                for (size_t i = 0; i < 3; i++)
                        output[j] += a[i] * b[i][j];
        }
        // bias et softmax

	printf ("\n\nOutput = \t");
    for (int i = 0; i < 3; i++)
    {
        printf("%f\n\t\t", output[i]);
    }
	printf("\n");

	printf("%f\n", exp(1.6578));

	//printf("\n%f\n\n", exp(1.0000));
*/

	// ----------------------------
	// STEP 4 : GUI AND TEXT EXPORT
	// ----------------------------
	return 0;
}
