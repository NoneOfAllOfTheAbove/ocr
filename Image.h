#ifndef IMAGE_H
#define IMAGE_H

unsigned char **CreateImageMatrix(int width, int height);
unsigned char **ImageToGrayscale(char imagePath[], int *imageWidth, int *imageHeight);
unsigned char **GrayscaleToBinarized(unsigned char **grayscaleImageMatrix, int imageWidth, int imageHeight);

#endif