#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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

	// ----------------------------
	// STEP 4 : GUI AND TEXT EXPORT
	// ----------------------------

	return 0;
}