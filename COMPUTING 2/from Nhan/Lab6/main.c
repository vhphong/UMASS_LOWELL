#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

int main(int argc, char* argv[]) {
  int i;
  MY_STRING string_array[100] = {NULL};
  string_array[0] = my_string_init_c_string("COPY ME!");
  for (i = 1; i < 100; ++i) {
    my_string_assignment(&string_array[i], string_array[0]);
  }

   for (i = 0; i < 100; ++i) {
    my_string_insertion(string_array[i], stdout);
    printf("\n");
    my_string_destroy(&string_array[i]);
  } 
  return 0;
}