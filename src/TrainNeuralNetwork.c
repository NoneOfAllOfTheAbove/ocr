#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <sys/stat.h> // for mkdir

#include "Matrix.h"
#include "Preprocessing/Preprocessing.h"
#include "Segmentation/Segmentation.h"
#include "NeuralNetwork/NeuralNetwork.h"
#include "GUI/DemoGUI.h"

void TrainNeuralNetwork()
{
	int total = 0;
	int characterId = 0;
	for(int a = 62; a < 62 + 24; a++)
	{
		char dir[100] = "";
		snprintf(dir, sizeof(dir), "docs/nn-training-dataset/%d", a);
		mkdir(dir, 0700);
	}
	for(int i = 1; i < 2; i++)
	{
		Image image;
		char path[100] = "";
		snprintf(path, sizeof(path), "docs/nn-training-dataset/Capture%d.png", i);
		image.path = path;
		image = LoadImageAsGrayscale(image);
		image = BinarizeImage(image);
		Text text = Segmentation(image);
		StartDemoGUI(image, text);
		printf("----- %s \n", path);

		for(int p = 0; p < text.numberOfParagraphs; p++)
		{
			for (int l = 0; l < text.paragraphs[p].numberOfLines; l++)
			{
				for (int w = 0; w < text.paragraphs[p].lines[l].numberOfWords; w++)
				{
					for (int c = 0; c < text.paragraphs[p].lines[l].words[w].numberOfCharacters; c++)
					{
						char path[100] = "";
						snprintf(path, sizeof(path), "docs/nn-training-dataset/%d/%d.png", 62 + characterId, total / 24);

						Character character = text.paragraphs[p].lines[l].words[w].characters[c];
						unsigned char **matrix = character.matrix;
						// printf("%s \n", path);
						if (character.x2 - character.x1 > 0 && character.y2 - character.y1 > 0)
						{
							SaveMatrixAsImage(matrix, 16, 16, path);
						}

						total++;
						characterId++;
						characterId = characterId % 24;
					}
				}
			}
		}
	}
}
