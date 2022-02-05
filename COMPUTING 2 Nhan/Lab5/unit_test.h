#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "my_string.h"
Status test_init_default_returns_nonNULL(char* buffer, int length);
Status test_get_size_on_init_default_returns_0(char* buffer, int length);
Status test_get_capacity_on_init_default_returns_7(char* buffer, int length);
Status test_init_c_string_returns_nonNULL(char* buffer, int length);
Status test_get_size_on_init_c_string_returns_non_0(char* buffer, int length);
Status test_get_capacity_on_init_c_string_compare_with_size(char* buffer, int length);
Status test_my_string_extraction_return_nonNULL(char* buffer, int length);
Status test_my_string_insertion_return_SUCCESS(char* buffer, int length);
Status test_my_string_push_back_return_SUCCESS(char* buffer, int length);
#endif
