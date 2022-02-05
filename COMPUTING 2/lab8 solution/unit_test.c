#include <stdio.h>
#include "unit_test.h"

int main(int argc, char* argv[]) {
Status (*tests[])(char*, int) =
  {
    test_dbaumann_init_default_returns_nonNULL,
    test_dbaumann_handle_set_to_NULL_after_string_destroy,
    test_dbaumann_get_size_on_init_default_returns_0,
    test_dbaumann_get_capacity_on_init_default_returns_7,
    test_dbaumann_init_c_string_returns_nonNULL,
    test_dbaumann_get_size_on_init_c_string_returns_string_length,
    test_dbaumann_get_capacity_on_init_c_string_returns_string_length_plus_one,
    test_dbaumann_string_compare_on_a_and_an_less_than_0,
    test_dbaumann_string_compare_on_an_and_a_greater_than_0,
    test_dbaumann_string_extraction_returns_success_on_succressful_read,
    test_djbaumann_string_extraction_reads_correct_string,
    test_dbaumann_string_insertion_returns_success_on_successful_write,
    test_dbaumann_push_back_returns_success_pushing_char_on_empty_default_string,
    test_dbaumann_push_back_returns_success_pushing_char_on_full_string,
    test_dbaumann_push_back_doubles_string_capacity_on_resize,
    test_dbaumann_push_back_increments_size_by_one,
    test_dbaumann_pop_back_returns_success_on_non_empty_string,
    test_dbaumann_pop_back_decrements_size_by_one,
    test_dbaumann_pop_back_returns_failure_on_empty_string,
    test_dbaumann_string_at_returns_valid_character_pointer,
    test_dbaumann_c_str_does_not_change_string_size,
    test_dbaumann_string_concat_does_not_modify_hAppend_string,
    test_dbaumann_c_str_returns_correct_string,
    test_dbaumann_string_empty_returns_true_on_empty_string,
    test_dbaumann_string_empty_returns_false_on_non_empty_string
  };
  int number_of_functions = sizeof(tests) / sizeof(tests[0]);
  int i;
  char buffer[500];
  int success_count = 0;
  int failure_count = 0;

  for(i=0; i<number_of_functions; i++) {
    if(tests[i](buffer, 500) == FAILURE) {
        printf("FAILED: Test %d failed miserably\n", i);
        printf("\t%s\n", buffer);
        failure_count++;
    }
    else {
      printf("PASS: Test %d passed\n", i);
      printf("\t%s\n", buffer);
      success_count++;
    }
  }
  printf("Total number of tests: %d\n", number_of_functions);
  printf("%d/%d Pass, %d/%d Failure\n", success_count,number_of_functions,
    failure_count, number_of_functions);
  return 0;
}
