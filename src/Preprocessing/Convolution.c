#include "Preprocessing.h"
#include "../Matrix.h"
#include "math.h"
#include "stdio.h"

unsigned char **ApplyFilter(Image image, double filter[9])
{

    int size_x = image.width;
    int size_y = image.height;

    unsigned char **tmp_matrix = CreateCharMatrix(size_x, size_y);

    //Traversing image.matrix
    for (size_t x = 1; x < size_y-1; x++)
    {
        for (size_t y = 1; y < size_x-1; y++)
        {

            size_t filter_index = 0;

            double sum = 0;
            double divisor = 0;

            //Applying matrix
            for (size_t index_y = y - 1; index_y < y + 2; index_y++)
            {
                for (size_t index_x = x - 1; index_x < x + 2; index_x++)
                {
                    //Skipping particular cases (out of bound, (x,y))
                    if (index_x == -1 || index_x >= size_x || index_y == -1 ||
                        index_y >= size_y)
                        {filter_index++; continue;}

                sum += ((double) image.grayscale[y][x]) * filter[filter_index];
                divisor += filter[filter_index];
                filter_index++;

                }
            }

            tmp_matrix[y][x] = (char) (sum / divisor);
        }
    }

return tmp_matrix;

}

//cf https://en.wikipedia.org/wiki/Kernel_(image_processing)

void Blur(Image image)
{
    double filter[9] = {1,1,1,1,1,1,1,1,1};
    image.grayscale = ApplyFilter(image, filter);
}

void GaussianBlur(Image image)
{
    double filter[9] = {1,2,1,2,4,2,1,2,1};
    image.grayscale = ApplyFilter(image, filter);
}

//High pass filter
void Sharpen(Image image)
{
    double filter[9] = {0,-1,0,-1,5,-1,0,-1,0};
    image.grayscale = ApplyFilter(image, filter);
}

//Sobel operator
void EdgeDetection(Image image)
{
    double filter[9] = {-1,-1,-1,-1,8,-1,-1,-1,-1};
    image.grayscale = ApplyFilter(image, filter);
}

void SobelsEdgeDetection(Image image)
{
    GaussianBlur(image);

    double filter_gx[9] = {-1,0,1,-2,0,2,-1,0,1};
    unsigned char **matrix_gx = ApplyFilter(image, filter_gx);

    double filter_gy[9] = {-1,-2,-1,0,0,0,1,2,1};
    unsigned char **matrix_gy = ApplyFilter(image, filter_gy);

    int size_x = image.width;
    int size_y = image.height;

    for (size_t x = 0; x < size_y; x++)
    {
        for (size_t y = 0; y < size_x; y++)
        {
            double gradient = sqrt( pow(matrix_gx[y][x], 2)
            + pow(matrix_gy[y][x], 2) );
            image.grayscale[y][x] = (char)(((double)image.grayscale[y][x]
            + gradient)/2);
        }
    }
}
