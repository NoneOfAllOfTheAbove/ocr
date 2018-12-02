#include <stdio.h>
#include <math.h>

#include "Preprocessing.h"
#include "../Matrix.h"
#include "Filters.h"

Image ApplyFilter(Image image, double *filter, int divisor)
{
	int size_x = image.width;
	int size_y = image.height;

	unsigned char **tmp_matrix = CreateCharMatrix(size_x, size_y);
	for (size_t x = 0; (int)x < size_x; x++)
	{
		for (size_t y = 0; (int)y < size_y; y++)
		{
			tmp_matrix[y][x] = image.grayscale[y][x];
		}
	}

	//Traversing image.matrix
	for (size_t x = 1; (int)x < size_x-1; x++)
	{
		for (size_t y = 1; (int)y < size_y-1; y++)
		{
			size_t filter_index = 0;
			double summ = 0;

			//Applying matrix
			for (size_t index_y = y - 1; index_y < y + 2; index_y++)
			{
				for (size_t index_x = x - 1; index_x < x + 2; index_x++)
				{
					//Skipping particular cases (out of bound, (x,y))
					if ((int)index_x < 0 || (int)index_x >= size_x
					|| (int)index_y < 0 || (int)index_y >= size_y)
						{filter_index++; continue;}

					summ += ((double) image.grayscale[index_y][index_x]
					* filter[filter_index]);

					filter_index++;
				}
			}
			tmp_matrix[y][x] = (char) round(summ / divisor);
		}
	}
	image.grayscale = tmp_matrix;
	return image;
}

//cf https://en.wikipedia.org/wiki/Kernel_(image_processing)

Image Blur(Image image)
{
	double filter[9] = {1,1,1,1,1,1,1,1,1};
	image = ApplyFilter(image, filter, 9);

	return image;
}

Image GaussianBlur(Image image)
{
	double filter[9] = {1,2,1,2,4,2,1,2,1};
	image = ApplyFilter(image, filter, 16);

	return image;
}

//High pass filter
Image Sharpen(Image image)
{
	double filter[9] = {0,-1,0,-1,5,-1,0,-1,0};
	image = ApplyFilter(image, filter, 1);

	return image;
}

//Sobel operator
Image EdgeDetection(Image image)
{
	double filter[9] = {-1,-1,-1,-1,8,-1,-1,-1,-1};
	image = ApplyFilter(image, filter, 1);

	return image;
}

Image SobelsEdgeDetection(Image image)
{
	GaussianBlur(image);

	double filter_gx[9] = {-1,0,1,-2,0,2,-1,0,1};
	unsigned char **matrix_gx = ApplyFilter(image, filter_gx, 1).grayscale;

	double filter_gy[9] = {-1,-2,-1,0,0,0,1,2,1};
	unsigned char **matrix_gy = ApplyFilter(image, filter_gy, 1).grayscale;

	int size_x = image.width;
	int size_y = image.height;

	for (size_t x = 1; (int)x < size_x-1; x++)
	{
		for (size_t y = 1; (int)y < size_y-1; y++)
		{
			double gradient = sqrt(
				pow(matrix_gx[y][x], 2) +
				pow(matrix_gy[y][x], 2)
			);
			//printf("%f\n", gradient);
			//image.grayscale[y][x] =
				// (char)(((double)image.grayscale[y][x] + gradient)/2);
			image.grayscale[y][x] = gradient;
		}
	}

	return image;
}
