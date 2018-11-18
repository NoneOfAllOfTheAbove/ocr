#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <sys/stat.h>

#include "../OCR/Matrix.h"
#include "../OCR/NeuralNetwork/NeuralNetwork.h"

void PrepareSecialCharsDataset()
{
	/*int total = 0;
	int characterId = 0;
	for(int a = 62; a < 62 + 24; a++)
	{
		char dir[100] = "";
		snprintf(dir, sizeof(dir), "docs/nn-training-dataset/%d", a);
		mkdir(dir, 0700);
	}
	for(int i = 1; i <= 78; i++)
	{
		Image image;
		char path[100] = "";
		snprintf(path, sizeof(path), "docs/nn-training-dataset/data_training page %d.png", i);
		printf("Loading %s \n", path);
		image.path = path;
		image = LoadImageAsGrayscale(image);
		image = BinarizeImage(image);
		Text text = Segmentation(image);
		//StartDemoGUI(image, text);

		for(int p = 0; p < text.numberOfParagraphs; p++)
		{
			for (int l = 0; l < text.paragraphs[p].numberOfLines; l++)
			{
				for (int w = 0; w < text.paragraphs[p].lines[l].numberOfWords; w++)
				{
					int test = text.paragraphs[p].lines[l].words[w].numberOfCharacters;
					if(i == 37 && l == 0 && w == 0)
					{
						test = 1;
					}
					for (int c = 0; c < test; c++)
					{
						char path[100] = "";
						snprintf(path, sizeof(path), "docs/nn-training-dataset/%d/%d.png", 62 + characterId, total / 24);
						
						Character character = text.paragraphs[p].lines[l].words[w].characters[c];
						if(character.x2 - character.x1 > 0 && character.y2 - character.y1 > 0)
						{
							SaveMatrixAsImage(character.matrix, 16, 16, path);
							total++;
							characterId++;
							characterId = characterId % 24;
						}
					}
				}
			}
		}
	}*/
}

void TrainNeuralNetwork()
{
	printf("Your turn Ari ;)\n");
}

int main()
{
	TrainNeuralNetwork();

	return 0;
}
