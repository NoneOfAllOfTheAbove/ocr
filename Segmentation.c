// Input the matrix in B&W only (0/1 matrix)
void Labelling(double **matrix)
{
  int x,y;

  //Creating an array of matrix's size to store labels

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

void _CheckNeighbours(int x, int y, int labels[][], double **matrix)
{
  //Checking the 8 neighbours.
  //For each neighbours, if it is black we check in labels for labels
  //If the neighbour has a label, the current pixel copies its label

  if (x - 1 > 0)
    {
      if
    }
}
