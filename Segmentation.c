#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#include "Segmentation.h"
// -------------------------------------------------------------------
// ---------------- Building structure for label equivalences storing
// -------------------------------------------------------------------

 /*typedef struct {
  unsigned char *array;
  size_t used;
  size_t size;
} Array ;*/

void initArray(Array *a, size_t initialSize) {
  a->array = (unsigned char *)malloc(initialSize * sizeof(unsigned char));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(Array *a, unsigned char element) {
  if (a->used == a->size) {
    a->size *= 2;
    a->array =
    (unsigned char *)realloc(a->array, a->size * sizeof(unsigned char));
  }
  a->array[a->used++] = element;
}

void freeArray(Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

Array equivalences;

// -------------------------------------------------------------------
// --------------------------------------- Tools for creating **labels
// ---------**labels has the same size of **matrix and contains labels
// -------------------------------------------------------------------

int **BuildMatrix(size_t line, size_t column)
{
	int **matrix = (int **) malloc(sizeof(int *) * line);
        if (matrix == NULL)
                exit(0);
	for (size_t i = 0; i < line; i++)
        {
                *(matrix + i) = (int *) malloc(sizeof(int) * column);

        }
	return matrix;
}

int **labels;
int label_count = 1;


// -------------------------------------------------------------------
// ---------------------- Subfunctions of the labelling algorithm
// -------------------------------------------------------------------

int imageWidth, imageHeight;
void CheckNeighbours(int x, int y)
{
  //Checking the 8 neighbours.
  //For each neighbours, if it is black we check its label in labels[]
  //If the neighbour has one label, the current pixel copies it
  //If there are different labels in the neighbourhood, current pixel



  //Matrix traversal variables
  int index_x, index_y;
  int size_x = imageWidth;
  int size_y = imageHeight;

  //Neighbours traversal variables
  int neighbours_labels[8];
  for (size_t i = 0; i < 8; i++)
  {
      neighbours_labels[i] = 0;
  }
  int neighbours_labeled = 0;
  int neighbours_count = 0;


  //Traversing labels[][]
  for (index_y = y - 1; index_y < y+2; index_y++)
  {
    for (index_x = x - 1; index_x < x+2; index_x++)
    {
      //Skipping particular cases (out of bound, (x,y))
      if (index_x == -1 || index_x >= size_x || index_y == -1 ||
          index_y >= size_y || (index_x == x && index_y == y))
      {
        neighbours_count++;
        continue;
      }
      //Checking if neighbour(index_x,index_y) has already a label
      int tmp_label = labels[index_y][index_x];
      //printf("Neighbour (%i,%i) has label : %i\n", index_x, index_y, labels[index_y][index_x]);
      if (tmp_label != 0)
        {
            //printf("%s\n", "Label is not zero");
            neighbours_labeled +=1;
            neighbours_labels[neighbours_count] = tmp_label;
            neighbours_count++;
        }
    }
  }

  //If one or more neighbours had a label, we go through neighbours_labels[]
  //to store equivalences and set the smallest label to current pixel
  if (neighbours_labeled != 0)
  {
    int min_label = neighbours_labels[0];

    for(size_t i = 1; i < 8; i++)
    {
      int tmp_label = neighbours_labels[i];
      if (tmp_label != 0)
      {
        if (tmp_label > min_label)
        {
          equivalences.array[tmp_label - 1] = min_label;
        }
        else
        {
          if (tmp_label < min_label)
          {
            equivalences.array[min_label - 1] = tmp_label;
            min_label = tmp_label;
          }
        }
      }
    }
    labels[y][x] = min_label;
  }
  //Otherwise we create a new label
  else
  {
    insertArray(&equivalences, 0);
    labels[y][x] = label_count;
    label_count++;
  }
}

void Labelling_FirstPass(unsigned char **matrix)
{
  //We create an array of matrix's size to store labels

  // labels[y][x]
  labels = BuildMatrix(imageHeight, imageWidth);

  //Initializing labels[y][x] properly
  for (size_t y = 0; (int) y < imageHeight; y++)
  {
    for (size_t x = 0; (int) x < imageWidth; x++)
    {
      labels[y][x] = 0;
    }
  }

  //Initializing the equivalences array
  initArray(&equivalences, 1);

  //Going through the B&W matrix, calling CheckNeighbours
  //when the pixel is black


  for (size_t y = 0; (int) y < imageHeight; y++)
  {
    for (size_t x = 0; (int) x < imageWidth; x++)
    {
        //printf("(%li,%li) = %u\n", x, y, matrix[y][x]);
        if (matrix[y][x] != 0)
        {
            //printf("%s\n", "Checking neighbours");
            CheckNeighbours(x, y);
        }
    }
  }

}

// useful_labels is an array containing only labels without smaller equivalences

Array useful_labels;

void Labelling_SecondPass()
{
  initArray(&useful_labels, 1);

  //Going through the labels matrix, replacing equivalent labels
  for (size_t y = 0; (int) y < imageHeight; y++)
  {
    for (size_t x = 0; (int) x < imageWidth; x++)
    {
      //If an equivalent label is set, we replace the current one
      if (equivalences.array[(int) labels[y][x]] != 0)
      {
        labels[y][x] = equivalences.array[(int) labels[y][x]];
      }
      else
      {
        insertArray(&useful_labels, labels[y][x]);
      }
    }
  }
  useful_labels.array[0] = useful_labels.used;
  freeArray(&equivalences);
}


Array characters;
unsigned char *Labelling_GetCharacters()
{

    initArray(&characters, 1);

    for (size_t i = 0; i < useful_labels.used; i++)
    {
        int min_x, max_x, min_y, max_y;
        _Bool first_met = false;

        //For each label, we do a traversal of labels to get the coordinates
        //of the top-left and bottom-right corners of the character's frame
        for (size_t y = 0; (int) y < imageHeight; y++)
        {
            for (size_t x = 0; (int) x < imageWidth; x++)
            {
                if (labels[y][x] == useful_labels.array[i])
            {
                if (first_met)
                {
                    if (min_x > (int) x){min_x = (int) x;}
                    if (max_x < (int) x){max_x = (int) x;}
                    if (min_y > (int) y){min_y = (int) y;}
                    if (max_y < (int) y){max_y = (int) y;}
                }
                else
                {
                    min_x = max_x = (int) x;
                    min_y = max_y = (int) y;
                }
          }
      }
    }

    insertArray(&characters, min_x);
    insertArray(&characters, max_x);
    insertArray(&characters, min_y);
    insertArray(&characters, max_y);
  }

  freeArray(&useful_labels);
  characters.array[0] = characters.used;
  return characters.array;
}

// -------------------------------------------------------------------
// ---------------------------------------------------- Main functions
// -------------------------------------------------------------------

Array blocs;

unsigned char *Bloc_Detection(unsigned char **matrix)
{
    initArray(&blocs, 1);
    int bloc_status = 0;

    for (size_t x = 0; (int) x < imageWidth; x++)
    {
        _Bool white_column = true;

        for (size_t y = 0; (int) y < imageHeight; y++)
        {
            if (bloc_status == 0)
            {
                if (matrix[y][x] != 0)
                {
                    bloc_status ++;
                    insertArray(&blocs, (int) x);
                    break;
                }
            }
            else
            {
                if (matrix[y][x] != 0){white_column = false;}
            }
        }

        if (white_column)
        {
            insertArray(&blocs, (int) x);
            bloc_status--;
        }
    }

    if (bloc_status != 0)
    {
        insertArray(&blocs, (int) imageWidth - 1);
    }

    //Returns the list of x coordinates of blocs
    blocs.array[0] = blocs.used;
    return blocs.array;
}

Array lines;
unsigned char *Line_Detection(unsigned char **matrix, unsigned char *xblocs)
{

    initArray(&lines, 1);

    for (size_t b = 0; b < xblocs[0]; b+=2)
    {
        int line_status = 0;
        for (size_t y = 0; (int) y < imageHeight; y++)
        {
            _Bool white_line = true;

            for (size_t x = (int) xblocs[(int) b];
             x < xblocs[(int) b+1]; x++)
             {
                 if (line_status == 0)
                 {
                     if (matrix[y][x] != 0)
                     {
                         line_status ++;
                         insertArray(&lines, (int) x);
                         insertArray(&lines, (int) y);
                         break;
                     }
                 }
                 else
                 {
                     if (matrix[y][x] != 0){white_line = false;}
                 }
             }
             if (white_line)
             {
                 insertArray(&lines, (int) xblocs[(int) b+1]);
                 insertArray(&lines, (int) y);
                 line_status--;
             }
        }
        if (line_status != 0)
        {
            insertArray(&lines, (int) xblocs[(int) b+1]);
            insertArray(&blocs, (int) imageHeight - 1);
        }
    }
    lines.array[0] = lines.used;
    return lines.array;
}

// -------------------------------------------------------------------
// ---------------------------------------------------- Main functions
// -------------------------------------------------------------------

// Input the matrix in B&W only (0-1 matrix)
unsigned char *Labelling(unsigned char **matrix, int width, int height)
{
    imageWidth = width;
    imageHeight = height;

    //printf("%s\n", "Calling first pass...");

    Labelling_FirstPass(matrix);
    Labelling_SecondPass();
    unsigned char *chars = Labelling_GetCharacters();
    freeArray(&characters);

    //Returns list n*4 of top-left and bottom-right corner coords of characters
    return chars;
}

unsigned char *Bloc_Line_Detection(unsigned char **matrix)
{
    unsigned char *blocs_x = Bloc_Detection(matrix);
    freeArray(&blocs);
    unsigned char *line = Line_Detection(matrix, blocs_x);
    freeArray(&lines);
    return line;
}

//int main(){return 0;}
