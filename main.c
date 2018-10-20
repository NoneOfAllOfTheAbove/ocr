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
	double output1[] = {1, 0};

	double input2[] = {0, 1};
	double output2[] = {1, 0};
	
	double input3[] = {1, 1};
	double output3[] = {0, 1};

	double input4[] = {0, 0};
	double output4[] = {0, 1};

	Start(2, 4, 2);
	

	printf("\n    Before Training :\n\n[1-0 -> 1]");
	Predict(input1);
	
	printf("[0-1 -> 1]");
	Predict(input2);

	printf("[1-1 -> 0]");
	Predict(input3);

	printf("[0-0 -> 0]");
	Predict(input4);

	printf("\n\n\n");

	//printf("\n\n----------------------------------------------------------\n\n");

	srand(time(NULL));
	long t;
	for (int i = 0; i < 150000; i++)
	{
		t = rand() % 4;
		//printf("%ld \n", t);
		if (t == 0)
		{
			Train(input1, output1);
		}
		if (t == 1)
		{
			Train(input2, output2);
		}
		if (t == 2)
		{
			Train(input3, output3);
		}
		else
		{
			Train(input4, output4);
		}
	}

	printf("    After training :\n\n[1-0 -> 1]");
	Predict(input1);
	
	printf("[0-1 -> 1]");
	Predict(input2);

	printf("[1-1 -> 0]");
	Predict(input3);

	printf("[0-0 -> 0]");
	Predict(input4);

	// ----------------------------
	// STEP 4 : GUI AND TEXT EXPORT
	// ----------------------------
	return 0;
}
