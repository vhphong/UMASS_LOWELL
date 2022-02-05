#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "generic_vector.h"


int main(int argc, char* argv[]) {
  /* array of vectors of strings
  read strings to temp string from dictionary
  copy temp string to vector of right string size in array
  */
  G_VECTOR hVector[30] = { NULL };
  MY_STRING tempString = NULL;
  FILE* dictionary = NULL;
  int i;
  //init objects
  //populate array
  for (i = 0; i < 30; ++i) {
    hVector[i] = generic_vector_init_default(my_string_assignment, my_string_destroy);
    if (hVector[i] == NULL) {
      printf("Did not create vector\n");
      exit(1);
    }
  }
  tempString = my_string_init_c_string("Hello");
  if (tempString == NULL){
    printf("Did not create string\n");
    exit(1);
  }
  dictionary = fopen("dictionary.txt", "r");
  if (dictionary == NULL) {
    printf("Could not open dictionary.txt\n");
    exit(1);
  }
  // populate vectors
  while(my_string_extraction(tempString, dictionary) == SUCCESS) {
    if (my_string_get_size(tempString) < 30) {
      generic_vector_push_back(hVector[my_string_get_size(tempString)], tempString);
    }
  }
  //print values
  for (i = 0; i < 30; ++i) {
    printf("Number of strings with %d characters: %d\n", i, generic_vector_get_size(hVector[i]));
  }
  for (i = 0; i < 30; i++) {
    generic_vector_destroy(&(hVector[i]));
  }
  fclose(dictionary);
  my_string_destroy(&tempString);
  return 0;
}

	}
	fclose(dictionary);
	my_string_destroy(&tempString);
	return 0;
}