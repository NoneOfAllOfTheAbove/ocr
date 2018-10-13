int label_count = 1;

// Input the matrix in B&W only (0-1 matrix)
void Labelling(double **matrix)
{
  int x,y;

  //We create an array of matrix's size to store labels

  // labels[y][x]
  int labels[sizeof(matrix)][sizeof(matrix[0])]

  //Initializing labels[y][x] properly
  for (y = 0; y < sizeof(labels); y++)
  {
    for (x = 0; x < sizeof(labels[0]); x++)
    {
      labels[y][x] = 0
    }
  }

  x,y = 0,0

  //Going through the B&W matrix, calling CheckNeighbours
  //when the pixel is black
  for (x = 0; x < sizeof(matrix[0]); x++)
  {
    for (y = 0; y < sizeof(matrix); y++)
    {
      if (matrix[y][x] == 1)
      {
        labels = _CheckNeighbours(x,y, labels, matrix)
      }
    }
  }

}

int[][] _CheckNeighbours(int x, int y, int labels[][], double **matrix)
{
  //Checking the 8 neighbours.
  //For each neighbours, if it is black we check in labels for labels
  //If the neighbour has a label, the current pixel copies its label

  int index_x, index_y;
  int size_x, size_y = sizeof(labels[0]), sizeof(labels);
  int labelled = 0;

  for (index_x = x - 1; index_x < x+2; index_x++)
  {
    //Skipping out of bounds cases
    if (index_x == -1 || index_x >= size_x)
    {
      continue;
    }
    for (index_y = y - 1; index_y < y+2); index_y++)
    {
      //Skipping particular cases (out of bound, (x,y))
      if (index_y == -1 || index_y >= size_y || (index_x == x && index_y == y))
      {
        continue;
      }

      //Checkinf if the neighbour (index_x,index_y) has already a label
      int tmp_label = labels[index_y][index_x];
      if (tmp_label != 0)
        {
          //If true, int label is assigned the neighbour's label
          label = tmp_label;
          break;
        }
    }
  }

  //If label has been set during the loop, storing it in labels[][]
  if (label != 0)
  {
    labels[index_y][index_x] = label;
  }
  //Otherwise we create a new label
  else
  {
    labels[index_y][index_x] = label_count;
    label_count++;
  }

  return labels;
}
