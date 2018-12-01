#ifndef FILTERS_H
#define FILTERS_H

Image ApplyFilter(Image image, double filter[9], int divisor);
Image Blur(Image image); // 1
Image EdgeDetection(Image image);
Image GaussianBlur(Image image); // 3
Image Sharpen(Image image); // 2
Image SobelsEdgeDetection(Image image);

#endif