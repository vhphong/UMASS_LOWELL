#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

int main(int argc, char* argv[]) {
  MY_STRING hMy_string1 = NULL;
  MY_STRING hMy_string2 = NULL;

  hMy_string1 = my_string_init_c_string("hi");
  hMy_string2 = my_string_init_c_string("hill");

  printf("'hi' was made with capacity %d and size %d\n",
    my_string_get_capacity(hMy_string1), my_string_get_size(hMy_string1));

  printf("'hill' was made with capacity %d and size %d\n",
    my_string_get_capacity(hMy_string2), my_string_get_size(hMy_string2));

  printf("Comparing 'hi' to 'hill' yields: %d\n",
    my_string_compare(hMy_string1, hMy_string2));

  printf("Comparing 'hill' to 'hi' yields: %d\n",
    my_string_compare(hMy_string2, hMy_string1));

  printf("Comparing 'hi' to 'hi' yields: %d\n",
    my_string_compare(hMy_string1, hMy_string1));

  my_string_destroy(&hMy_string1);
  my_string_destroy(&hMy_string2);
  return 0;
}#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

int main(int argc, char* argv[]) {
  MY_STRING hMy_string1 = NULL;
  MY_STRING hMy_string2 = NULL;

  hMy_string1 = my_string_init_c_string("hi");
  hMy_string2 = my_string_init_c_string("hill");

  printf("'hi' was made with capacity %d and size %d\n",
    my_string_get_capacity(hMy_string1), my_string_get_size(hMy_string1));

  printf("'hill' was made with capacity %d and size %d\n",
    my_string_get_capacity(hMy_string2), my_string_get_size(hMy_string2));

  printf("Comparing 'hi' to 'hill' yields: %d\n",
    my_string_compare(hMy_string1, hMy_string2));

  printf("Comparing 'hill' to 'hi' yields: %d\n",
    my_string_compare(hMy_string2, hMy_string1));

  printf("Comparing 'hi' to 'hi' yields: %d\n",
    my_string_compare(hMy_string1, hMy_string1));

  my_string_destroy(&hMy_string1);
  my_string_destroy(&hMy_string2);
  return 0;
}