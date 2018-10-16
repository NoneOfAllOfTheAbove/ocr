#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

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

	//Start(2, 3, 2);
	//PrintGlobalValues();

	double a[] = {4, 5, 6};
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


	// ----------------------------
	// STEP 4 : GUI AND TEXT EXPORT
	// ----------------------------
	return 0;
}
