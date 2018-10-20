#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Image.h"
#include "DemoGUI.h"

int main()
{
	// ----------------------------------------
	// STEP 1 : IMAGE LOADING AND PREPROCESSING
	// ----------------------------------------

	char imagePath[] = "test.png";
	int imageWidth, imageHeight;
	unsigned char **grayscaleImageMatrix = ImageToGrayscale(imagePath, &imageWidth, &imageHeight);
	unsigned char **binarizedImageMatrix = GrayscaleToBinarized(grayscaleImageMatrix, imageWidth, imageHeight);

	StartDemoGUI(imageWidth, imageHeight, grayscaleImageMatrix, binarizedImageMatrix);

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
