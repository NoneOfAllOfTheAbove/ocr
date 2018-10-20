#ifndef DEMOGUI_H
#define DEMOGUI_H

void DrawMatrix(SDL_Renderer *renderer, int width, int height, unsigned char **matrix);
void StartDemoGUI(int width, int height, unsigned char **grayscaleImageMatrix, unsigned char **binarizedImageMatrix);

#endif