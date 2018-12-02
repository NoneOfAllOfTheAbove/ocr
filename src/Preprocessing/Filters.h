#ifndef FILTERS_H
#define FILTERS_H

Image ApplyFilter(Image image, double filter[9], int divisor);
Image Blur(Image image);
Image EdgeDetection(Image image);
Image GaussianBlur(Image image);
Image Sharpen(Image image);
Image SobelsEdgeDetection(Image image);

#endif