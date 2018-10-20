unsigned char **CreateImageMatrix(int imageWidth, int imageHeight);
unsigned char **ImageToGrayscale(char imagePath[], int *imageWidth, int *imageHeight);
unsigned char **GrayscaleToBinarized(unsigned char **grayscaleImageMatrix, int imageWidth, int imageHeight);