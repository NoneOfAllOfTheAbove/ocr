#include <stdio.h>
#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Preprocessing/Preprocessing.h"
#include "Segmentation/Segmentation.h"
#include "NeuralNetwork/NeuralNetwork.h"
#include "GUI/GUI.h"
#include "GUI/DebugGUI.h"

int main(int argc, char** argv)
{
	// ----------------------
	// STEP 1 : PREPROCESSING
	// ----------------------

	if(argc != 2) {
		errx(1, "You must start the program by specifying the image's path as an argument.");
	}

	Image image;
	image.path = argv[1];
	image = LoadImageAsGrayscale(image);
	image = BinarizeImage(image);

	// ---------------------
	// STEP 2 : SEGMENTATION
	// ---------------------

	Text text = Segmentation(image);

	// -------------------------------
	// STEP 3 : CHARACTERS RECOGNITION
	// -------------------------------

	

	// ----------------------------
	// STEP 4 : GUI AND TEXT EXPORT
	// ----------------------------

	 StartGUI(argc, argv);
	//StartDebugGUI(image, text);

	return 0;
}
