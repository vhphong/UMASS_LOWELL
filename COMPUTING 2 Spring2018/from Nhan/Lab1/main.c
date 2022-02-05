#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  int **p;//Declaration of a pointer variable.
  //Declare 2D Malloc
  p = (int**)malloc(sizeof(int*)*20);//First "bookend" allocates space
  int i;
  for(i = 0; i < 20; i++)
    {
      p[i] = (int*)malloc(sizeof(int)*30);
    }
  //Put the number in
  for(int i = 0; i < 20; i++)
    {
      for(int j = 0; j < 30; j++)
	{
	  p[i][j] = j+i;
	  printf("%2d ", p[i][j]);
	}
      printf("\n");
    }
  //free
  for(i = 0; i < 20 ; i++)
    free(p[i]);
  free(p); //Second "bookend" cleans up the space
  return 0;
}