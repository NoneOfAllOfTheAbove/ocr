#ifndef PREPROCESSING_H
#define PREPROCESSING_H

typedef struct Image Image;
struct Image
{
	char *path;
	int width;
	int height;
	
	unsigned char **grayscale;
	unsigned char **binarized;
};

Image LoadImageAsGrayscale(Image);
Image BinarizeImage(Image);

#endif
