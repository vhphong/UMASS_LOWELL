#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

Status test_push_pop(); // tests push_back, pop_back, c_str, at
Status test_concat(); // tests concat

int main(int argc, char* argv[]) {
  int failures = 0;
  int successes = 0;
  printf("Testing Push, Pop, C-String, Empty, Address...\n");
  if (test_push_pop()) {
    printf("Success\n\n");
    ++successes;
  }
  else {
    printf("Failure\n\n");
    ++failures;
  }

  printf("Testing Concatenation...\n");
  if (test_concat()) {
    printf("Success\n\n");
    ++successes;
  }
  else {
    printf("Failure\n\n");
    ++failures;
  }
  printf("Total Successes: %d\n", successes);
  printf("Total Failures: %d\n", failures);
  return failures;
}

Status test_push_pop() {
  MY_STRING hMy_string = NULL;
  printf("Initializing...\n");
  hMy_string = my_string_init_c_string("a");
  do {
    if (hMy_string == NULL) {
      printf("Failed to initialize string object\n");
      break;
    }
    printf("String: \"%s\" size: %d, capacity: %d\n", my_string_c_str(hMy_string),
      my_string_get_size(hMy_string), my_string_get_capacity(hMy_string));

    printf("Testing push_back method...");
    if (!my_string_push_back(hMy_string, 'b')) {
      printf("Failed to resize string in push back\n");
      break;
    }
    printf("String: \"%s\" size: %d, capacity: %d\n", my_string_c_str(hMy_string),
      my_string_get_size(hMy_string), my_string_get_capacity(hMy_string));

    printf("Testing pop_back method twice...\n");
    if (!my_string_pop_back(hMy_string)) {
      printf("Cannot remove character: string already empty\n");
      break;
    }
    printf("String: \"%s\" size: %d, capacity: %d\n", my_string_c_str(hMy_string),
      my_string_get_size(hMy_string), my_string_get_capacity(hMy_string));
    if (!my_string_pop_back(hMy_string)) {
      printf("Cannot remove character: string already empty\n");
      break;
    }
    printf("String: \"%s\" size: %d, capacity: %d\n", my_string_c_str(hMy_string),
      my_string_get_size(hMy_string), my_string_get_capacity(hMy_string));

    printf("Testing empty method...\n");
    if (!my_string_empty(hMy_string)) {
      printf("String is not empty\n");
      break;
    }
    printf("String is empty\n");

    printf("Testing at method...\n");
    if (!my_string_push_back(hMy_string, 'a')) {
      printf("Failed to resize string in push back\n");
      break;
    }
    if (my_string_at(hMy_string, 0) == NULL) {
      printf("At method failed\n");
    }


    my_string_destroy(&hMy_string);
    return SUCCESS;
  } while(0);

  my_string_destroy(&hMy_string);
  return FAILURE;
}

Status test_concat() {
  MY_STRING hMy_string1 = NULL;
  MY_STRING hMy_string2 = NULL;
  MY_STRING TEST_STRING_1 = NULL;
  MY_STRING TEST_STRING_2 = NULL;
  printf("Initializing...\n");
  TEST_STRING_1 = my_string_init_c_string("abcd");
  TEST_STRING_2 = my_string_init_c_string("bcdabcd");
  hMy_string1 = my_string_init_c_string("a");
  hMy_string2 = my_string_init_default();
  do {
    if (hMy_string1 == NULL || hMy_string2 == NULL || TEST_STRING_1 == NULL ||
      TEST_STRING_2 == NULL) {
      printf("Failed to initialize string objects\n");
      break;
    }

    if (!my_string_push_back(hMy_string2, 'b')) {
      printf("Failed to resize string in push back\n");
      break;
    }
    if (!my_string_push_back(hMy_string2, 'c')) {
      printf("Failed to resize string in push back\n");
      break;
    }
    if (!my_string_push_back(hMy_string2, 'd')) {
      printf("Failed to resize string in push back\n");
      break;
    }

    printf("String 1: \"%s\" size: %d, capacity: %d\n", my_string_c_str(hMy_string1),
      my_string_get_size(hMy_string1), my_string_get_capacity(hMy_string1));
    printf("String 2: \"%s\" size: %d, capacity: %d\n", my_string_c_str(hMy_string2),
      my_string_get_size(hMy_string2), my_string_get_capacity(hMy_string2));

    printf("\nAppend String 2 to String 1:\n\n");
    if (!my_string_concat(hMy_string1, hMy_string2)) {
      printf("Failed to resize string in concatenation\n");
      break;
    }

    printf("String 1: \"%s\" size: %d, capacity: %d\n", my_string_c_str(hMy_string1),
      my_string_get_size(hMy_string1), my_string_get_capacity(hMy_string1));
    printf("String 2: \"%s\" size: %d, capacity: %d\n", my_string_c_str(hMy_string2),
      my_string_get_size(hMy_string2), my_string_get_capacity(hMy_string2));

    if (my_string_compare(TEST_STRING_1, hMy_string1)) {
      printf("Incorrect string created\n");
      break;
    }

    printf("\nAppend New String 1 to String 2:\n\n");
    if (!my_string_concat(hMy_string2, hMy_string1)) {
      printf("Failed to resize string in concatenation\n");
      break;
    }

    printf("String 1: \"%s\" size: %d, capacity: %d\n", my_string_c_str(hMy_string1),
      my_string_get_size(hMy_string1), my_string_get_capacity(hMy_string1));
    printf("String 2: \"%s\" size: %d, capacity: %d\n", my_string_c_str(hMy_string2),
      my_string_get_size(hMy_string2), my_string_get_capacity(hMy_string2));

    if (my_string_compare(TEST_STRING_2, hMy_string2)) {
      printf("Incorrect string created\n");
      break;
    }
    my_string_destroy(&TEST_STRING_1);
    my_string_destroy(&TEST_STRING_2);
    my_string_destroy(&hMy_string1);
    my_string_destroy(&hMy_string2);
    return SUCCESS;
  } while(0);
  my_string_destroy(&TEST_STRING_1);
  my_string_destroy(&TEST_STRING_2);
  my_string_destroy(&hMy_string1);
  my_string_destroy(&hMy_string2);
  return FAILURE;
}