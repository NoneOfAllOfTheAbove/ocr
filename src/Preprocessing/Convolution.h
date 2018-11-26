#ifndef KERNELCONVOLUTION_H
#define KERNELCONVOLUTION_H

unsigned char **ApplyFilter(Image image, double filter[9]);
void Blur(Image image);
void EdgeDetection(Image image);
void GaussianBlur(Image image);
void Sharpen(Image image);
void SobelsEdgeDetection(Image image);

#endif
