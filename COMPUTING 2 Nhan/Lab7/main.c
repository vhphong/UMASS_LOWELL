#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "generic_vector.h"


int main(int argc, char* argv[]) 
{

  G_VECTOR hVector[30] = { NULL };
  MY_STRING tempString = NULL;
  FILE* dictionary = NULL;
  int i;

  for (i = 0; i < 30; ++i) 
  {
    hVector[i] = generic_vector_init_default(my_string_assignment, my_string_destroy);
    if (hVector[i] == NULL) 
	{
      printf("Did not create vector\n");
      exit(1);
    }
  }
  tempString = my_string_init_c_string("Hello");
  if (tempString == NULL)
  {
    printf("Did not create string\n");
    exit(1);
  }
  dictionary = fopen("dictionary.txt", "r");
  if (dictionary == NULL) 
  {
    printf("Could not open dictionary.txt\n");
    exit(1);
  }
  // populate vectors
  while(my_string_extraction(tempString, dictionary) == SUCCESS) 
  {
    if (my_string_get_size(tempString) < 30) 
	{
      generic_vector_push_back(hVector[my_string_get_size(tempString)], tempString);
    }
  }
  //print values
  for (i = 0; i < 30; ++i) 
  {
	int size = generic_vector_get_size(hVector[i]);
    printf("Number of strings with %d characters: %d\n", i, generic_vector_get_size(hVector[i]));
	if(generic_vector_get_size(hVector[i])!=0)
	{
      printf("\tThe 0 word is %s\n", my_string_c_str(generic_vector_at(hVector[i], 0)));
      printf("\tThe %d word is %s\n", size-1, my_string_c_str(generic_vector_at(hVector[i], size-1)));
    }
  }
  for (i = 0; i < 30; i++) 
  {
    generic_vector_destroy(&(hVector[i]));
  }
  fclose(dictionary);
  my_string_destroy(&tempString);
  return 0;
}