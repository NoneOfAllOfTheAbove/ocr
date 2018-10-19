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

	// Create the grayscale and binarized matrices of the image
	double **grayscaleImageMatrix = CreateMatrix(imageWidth, imageHeight);
	double **binarizedImageMatrix = CreateMatrix(imageWidth, imageHeight);
	ImageToMatrices(imageSurface, grayscaleImageMatrix, binarizedImageMatrix);

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