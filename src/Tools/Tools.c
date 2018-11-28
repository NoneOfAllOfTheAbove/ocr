#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <sys/stat.h>
#include <time.h>

#include "../OCR/Matrix.h"
#include "../OCR/NeuralNetwork/NeuralNetwork.h"
#include "../OCR/Preprocessing/Preprocessing.h"

void PrepareSecialCharsDataset()
{/*
	int total = 0;
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


// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

//  TRRRRRRRAAAAAAAAAAIIIIIIIIIIIIIIINNIIIIIIIIIIIINNNNNNNG!!!!!!!



void GenerateTargetNN(double target[], int chosen)
{
    for (int i = 0; i < chosen; i++)
        target[i] = 0;
    target[chosen] = 1;
    for (int i = chosen + 1; i < 86; i++)
        target[i] = 0;
}


void GenerateInputNN(long character, long id, double input[])
{
    // recover the right image
    Image image;
    char path[100] = "";
    snprintf(path, sizeof(path), "resources/nn-training/dataset/%lu/%lu.png", character, id);
    image.path = path;
    image = LoadImageAsGrayscale(image);
    image = BinarizeImage(image);

    // image binarized : from 2D-matrice to 1D array
/*

    for (int i = 0; i < 256; i++)
    {
        if (i % 16 == 0)
            printf("\n");
            
        if (image.binarized[i / 16][i % 16] != 1)
            printf("   ");
        else
            printf("%d  ", image.binarized[i/16][i % 16]);
    }    
    printf("\n\n");*/

    
    // image binarized : from 2D-matrice to 1D array
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
            input[i * 16 + j] = (double) image.binarized[i][j];
    }
}


void TrainNeuralNetwork(size_t inputN, size_t hiddenN, size_t outputN, int tours, int mode)
{
    // create the NN
    Start(inputN, hiddenN, outputN);

    // load the nn.data maybe make a mode as before???
    if (mode)
        Load("resources/nn.data");
    
    // print Predict with the values before training?
    
    // sand the rand
    srand(time(NULL));

    // character : the number represented the char chosen randomly
    // id : the id of the image in the chosen char folder
    long int character, id;
    // int count = 0;
    for (int i = 0; i < tours; i++)
    {
        if (i % 1000 == 0)
        {
            printf("%d Done.\n", i);
        }   
    
        //print ("%d \n", i );

        character = rand() % 85; // change here
        id = rand() % 1016;

        // retrieve the good image --> an array 16*16 with doubles inside
        double input[256];
        GenerateInputNN(character, id, input);

        // now generate the right output of this number according to character
        double target[86];
        GenerateTargetNN(target, character);

       // printf("character : %ld,    id : %ld\n\n\n", character, id);


        /*
        for (int i = 0; i < 86; i++)
        {
            if (i % 10 == 0)
                printf("\n");
            printf("%f   ", target[i]);
        }
        printf("\n\n");*/




        // train with the input and the output.
        Train(input, target);
    }
    // save in nn.data
    Save("resources/nn.data");
}


char PredictionInterpretationNN(double output[])
{
    char res[86] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z', '"','(',')','=','+','-','_',47,'#','&','*', '/', 134, '[',']','{','}',',','.', ':','?','!',';','@'};

    int max = 0;
    for (int i = 0; i < 86; i++)
    {
        if (output[max] < output[i])
            max = i;
    }
    return res[max];
}



void PrintPredictNN(size_t inputN, size_t hiddenN, size_t outputN, int character, int id, int mode)
{
    if (mode)
    {
        Start(inputN, hiddenN, outputN);
        Load("resources/nn.data");
    }
    double input[256];
    GenerateInputNN(character, id, input);
    double *output = Predict(input);
    double target[86];
    GenerateTargetNN(target, character);
    printf("Expected result : %c\n", PredictionInterpretationNN(target));
    printf("result : %c\n\n\n", PredictionInterpretationNN(output));
}




int main(int argc, char** argv)
{

    // ******* TRAINING *******

    // if you train for the first time
    if (argc != 2)
        TrainNeuralNetwork(256, 86*4, 86, 1000000,0);
    // else
    else
    {
        unsigned long param = strtoul(argv[1], NULL,10);
        if (param == 1)
            TrainNeuralNetwork(256, 86*4, 86, 1000000,1);
        else
            TrainNeuralNetwork(256, 86*4, 86, 1000000,0);
    }



    // ******* PREDICT/TESTS *******

    /*srand(time(NULL));
    long int character, id;

    printf("******* Before training *******");

    Start(256, 86*5, 86);

    for (int i = 0; i < 10; i++)
    {
        character = rand() % 86; // change here
        id = rand() % 1016;
        
        printf("character : %ld,    id : %ld\n\n\n", character, id);

        PrintPredictNN(256, 86*5, 86, character, id, 0);
    }

    printf("\n\n\n******* After Training *******");

    character = rand() % 86; // change here
    id = rand() % 1016;
        
    printf("character : %ld,    id : %ld\n\n\n", character, id);

    PrintPredictNN(256, 86*5, 86, character, id, 1);

    


    for (int i = 0; i < 10; i++)
    {
        character = rand() % 86; // change here
        id = rand() % 1016;
        
        printf("character : %ld,    id : %ld\n\n\n", character, id);

        PrintPredictNN(256, 86*5, 86, character, id, 0);
    }*/


	return 0;
}
