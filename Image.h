void LoadImage(SDL_Surface **imageSurface, char imagePath[], int *imageWidth, int *imageHeight);
double** CreateMatrix(int width, int height);
void ImageToMatrices(SDL_Surface *imageSurface, double **grayscaleImageMatrix, double **binarizedImageMatrix);