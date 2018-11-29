#include <stdio.h>
#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Preprocessing/Preprocessing.h"
#include "Segmentation/Segmentation.h"
#include "NeuralNetwork/NeuralNetwork.h"
#include "GUI/GUI.h"
#include "GUI/DebugGUI.h"

char NNOutputToChar(double output[])
{
	char res[86] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '"', '(', ')', '=', '+', '-', '_', 47, '#', '&', '*', '/', 134, '[', ']', '{', '}', ',', '.', ':', '?', '!', ';', '@'};

	int max = 0;
	for (int i = 0; i < 86; i++)
	{
		if (output[max] < output[i])
			max = i;
	}
	return res[max];
}

void OCR_Start(char* path)
{
	// Start OCR
	Image image;
	image.path = path;
	image = LoadImageAsGrayscale(image);
	image = BinarizeImage(image);
	Start(256, 344, 86);
	Load("resources/nn.data");
	Text text = Segmentation(image);

	// Prepare outputText
	int numberOfCharacters = 0;
	for (int p = 0; p < text.numberOfParagraphs; p++)
	{
		for (int l = 0; l < text.paragraphs[p].numberOfLines; l++)
		{
			for (int w = 0; w < text.paragraphs[p].lines[l].numberOfWords; w++)
			{
				numberOfCharacters += text.paragraphs[p].lines[l].words[w].numberOfCharacters;
				numberOfCharacters += 1;
			}
			numberOfCharacters += 1;
		}
		numberOfCharacters += 2;
	}
	char outputText[numberOfCharacters];

	// Explore text
	int i = 0;
	for (int p = 0; p < text.numberOfParagraphs; p++)
	{
		for (int l = 0; l < text.paragraphs[p].numberOfLines; l++)
		{
			for (int w = 0; w < text.paragraphs[p].lines[l].numberOfWords; w++)
			{
				for (int c = 0; c < text.paragraphs[p].lines[l].words[w].numberOfCharacters; c++)
				{
					Character character = text.paragraphs[p].lines[l].words[w].characters[c];

					// Generate NN inputs
					double input[256];
					for (int i = 0; i < 16; i++)
					{
						for (int j = 0; j < 16; j++)
						{
							input[i * 16 + j] = (double)character.matrix[i][j];
						}
					}

					// Predict output
					double *output = Predict(input);
					char characterFound = NNOutputToChar(output);
					printf("%c \n", characterFound);

					outputText[i] = characterFound;
					i++;
				}
				outputText[i] = ' ';
				i++;
			}
			outputText[i] = '\n';
			i++;
		}
		outputText[i] = '\n';
		outputText[i + 1] = '\n';
		i += 2;
	}

	// Write text to GUI
	//StartDebugGUI(image, text);
	printf("%s \n", outputText);
}

void OCR_ExportAsTextFile()
{
	// TO DO
}

void OCR_Stop()
{
	// Free segmentation and image
}

int main(int argc, char** argv)
{
	StartGUI(argc, argv);

	return 0;
}