#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// -------------------------------------------------------------------
// ---------------- Building structure for label equivalences storing
// -------------------------------------------------------------------

typedef struct {
  double *array;
  size_t used;
  size_t size;
} Array;

void initArray(Array *a, size_t initialSize) {
  a->array = (double *)malloc(initialSize * sizeof(double));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(Array *a, double element) {
  if (a->used == a->size) {
    a->size *= 2;
    a->array = (double *)realloc(a->array, a->size * sizeof(double));
  }
  a->array[a->used++] = element;
}

void freeArray(Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

Array equivalences;
_Bool first_node_created = false;

// -------------------------------------------------------------------
// --------------------------------------- Tools for creating **labels
// ---------**labels has the same size of **matrix and contains labels
// -------------------------------------------------------------------

double** ConstructMatrix(size_t line, size_t column)
{
	double **matrix = (double **) malloc(sizeof(double *) * line);
        if (matrix == NULL)
                exit(0);
	for (size_t i = 0; i < line; i++)
        {
                *(matrix + i) = (double *) malloc(sizeof(double) * column);

        }
	return matrix;
}

double **labels;
int label_count = 1;


// -------------------------------------------------------------------
// ---------------------- Subfunctions of the labelling algorithm
// -------------------------------------------------------------------

void CheckNeighbours(int x, int y, double **matrix)
{
  //Checking the 8 neighbours.
  //For each neighbours, if it is black we check its label in labels[]
  //If the neighbour has one label, the current pixel copies it
  //If there are different labels in the neighbourhood, current pixel



  //Matrix traversal variables
  int index_x, index_y;
  int size_x = sizeof(matrix[0]);
  int size_y = sizeof(matrix);

  //Neighbours traversal variables
  int neighbours_labels[8];
  int neighbours_labeled = 0;
  int neighbours_count = 0;


  //Traversing labels[][]
  for (index_y = y - 1; index_y < y+2; index_y++)
  {
    //Skipping out of bounds cases
    if (index_y == -1 || index_y >= size_y)
    {
      neighbours_count++;
      continue;
    }
    for (index_x = x - 1; index_x < x+2; index_x++)
    {
      //Skipping particular cases (out of bound, (x,y))
      if (index_x == -1 || index_x >= size_x)
      {
        neighbours_count++;
        continue;
      }
      if (index_x == x && index_y == y)
      {
        neighbours_count++;
        continue;
      }

      //Checking if neighbour(index_x,index_y) has already a label
      int tmp_label = labels[index_y][index_x];
      if (tmp_label != 0)
        {
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

    for(size_t i = 1; i < sizeof(neighbours_labels); i++)
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
    if (first_node_created)
    {
      insertArray(&equivalences, 0);
    }
    else
    {
      equivalences.array[0] = 0;
      first_node_created = true;
    }

    labels[y][x] = label_count;
    label_count++;
  }
}

void Labelling_FirstPass(double **matrix)
{
  //We create an array of matrix's size to store labels

  // labels[y][x]
  labels = ConstructMatrix(sizeof(matrix), sizeof(matrix[0]));

  //Initializing labels[y][x] properly
  for (size_t y = 0; y < sizeof(labels); y++)
  {
    for (size_t x = 0; x < sizeof(labels[0]); x++)
    {
      labels[y][x] = 0;
    }
  }

  //Initializing the equivalences array
  initArray(&equivalences, 1);

  //Going through the B&W matrix, calling CheckNeighbours
  //when the pixel is black
  for (size_t y = 0; y < sizeof(matrix); y++)
  {
    for (size_t x = 0; x < sizeof(matrix[0]); x++)
    {
      if (matrix[y][x] == 1)
      {
        CheckNeighbours(x, y, matrix);
      }
    }
  }

}

// useful_labels is an array containing only labels without lower equivalences
Array useful_labels;

void Labelling_SecondPass()
{
  initArray(&useful_labels, 1);
  _Bool useful_labels_appended_once = false;

  //Going through the labels matrix, replacing equivalent labels
  for (size_t y = 0; y < sizeof(labels); y++)
  {
    for (size_t x = 0; x < sizeof(labels[0]); x++)
    {
      //If an equivalent label is set, we replace the current one
      if (equivalences.array[(int) labels[y][x]] != 0)
      {
        labels[y][x] = equivalences.array[(int) labels[y][x]];
      }
      else
      {
        if (useful_labels_appended_once)
        {
          insertArray(&useful_labels, labels[y][x]);
        }
        else
        {
          useful_labels.array[0] = labels[y][x];
          useful_labels_appended_once = true;
        }
      }
    }
  }
  freeArray(&equivalences);
}

Array Labelling_GetCharacters()
{
  Array characters;
  initArray(&characters, 4);
  _Bool characters_appended_once = false;

  for (size_t i = 0; i < useful_labels.used; i++)
  {
    int min_x, max_x, min_y, max_y;
    _Bool first_met = false;
    //For each label, we do a traversal of labels to get the coordinates of the
    //top-left and bottom-right corners of the character's frame
    for (size_t y = 0; y < sizeof(labels); y++)
    {
      for (size_t x = 0; x < sizeof(labels[0]); x++)
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

    if (characters_appended_once)
    {
      insertArray(&characters, min_x);
      insertArray(&characters, max_x);
      insertArray(&characters, min_y);
      insertArray(&characters, max_y);
    }
    else
    {
      characters.array[0] = min_x;
      characters.array[1] = max_x;
      characters.array[2] = min_y;
      characters.array[3] = max_y;

      characters_appended_once = true;
    }
  }

  freeArray(&useful_labels);
  return characters;
}
// Input the matrix in B&W only (0-1 matrix)
Array Labelling(double **matrix)
{
  Labelling_FirstPass(matrix);
  Labelling_SecondPass();
  return Labelling_GetCharacters();
}

int main(){return 0;}
