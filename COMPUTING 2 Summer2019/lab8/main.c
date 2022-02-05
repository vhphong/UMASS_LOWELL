#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_string.h"
#include "generic_vector.h"


//Precondition:current_word_family, new_key and word are all handles to valid
//   MY_STRING opaque objects.  guess is an alphabetical character that can be either
//   upper or lower case.
//Postcondition:  Returns SUCCESS after replacing the string in new_key with the key
//   value formed by considering the current word family, the word and the guess.
//   Returns failure in the case of a resizing problem with the new_key string.
Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess);


int main(int argc, char* argv[]) {
  /* Program from Lab 7:
  array of vectors of strings
  read strings to temp string from dictionary
  copy temp string to vector of right string size in array
  */
  /*G_VECTOR hVector[30] = { NULL };
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
  my_string_destroy(&tempString); */

	MY_STRING str1 = my_string_init_c_string("The");
	MY_STRING oldKey1 = my_string_init_c_string("---");
	MY_STRING newKey1 = my_string_init_default();
	
	MY_STRING str2 = my_string_init_c_string("Truck");
	MY_STRING oldKey2 = my_string_init_c_string("-----");
	MY_STRING newKey2 = my_string_init_default();
	
	MY_STRING str3 = my_string_init_c_string("happy");
	MY_STRING oldKey3 = my_string_init_c_string("--ppy");
	MY_STRING newKey3 = my_string_init_default();
	
	MY_STRING str4 = my_string_init_c_string("awesome");
	MY_STRING oldKey4 = my_string_init_c_string("--e---e");
	MY_STRING newKey4 = my_string_init_default();
	
	get_word_key_value(oldKey1, newKey1, str1, 'T');
	get_word_key_value(oldKey2, newKey2, str2, 'r');
	get_word_key_value(oldKey3, newKey3, str3, 'h');
	get_word_key_value(oldKey4, newKey4, str4, 'z');
	
	printf("%s\n", my_string_c_str(newKey1));
	printf("%s\n", my_string_c_str(newKey2));
	printf("%s\n", my_string_c_str(newKey3));
	printf("%s\n", my_string_c_str(newKey4));
	
	my_string_destroy(&str1);
	my_string_destroy(&str2);
	my_string_destroy(&str3);
	my_string_destroy(&str4);
	my_string_destroy(&oldKey1);
	my_string_destroy(&oldKey2);
	my_string_destroy(&oldKey3);
	my_string_destroy(&oldKey4);
	my_string_destroy(&newKey1);
	my_string_destroy(&newKey2);
	my_string_destroy(&newKey3);
	my_string_destroy(&newKey4);
	
	return 0;
}


Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess) {
	MY_STRING tempKey = NULL;
	Status status;
	char familyChar;
	char wordChar;
	tempKey = my_string_init_default();
	if (tempKey == NULL) {
		return FAILURE;
	}
	
	int i;
	guess = tolower(guess);
	for (i = 0; i < my_string_get_size(word); ++i) {
		familyChar = tolower(*(my_string_at(current_word_family, i)));
		wordChar = tolower(*(my_string_at(word, i)));
		if (guess == wordChar) {
			if (my_string_push_back(tempKey, guess) == FAILURE) {
				return FAILURE;
			}
		}
		else {
			if (my_string_push_back(tempKey, familyChar) == FAILURE) {
				return FAILURE;
			}
		}
	}
	status = my_string_assignment(&new_key, tempKey);
	my_string_destroy(&tempKey);
	return status;
}