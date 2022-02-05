#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_string.h"
#include "vector_string.h"
#include "binary_search_tree.h"

int get_word_length(void);
int get_no_of_guesses(void);
Boolean display_answer_or_not(void);
char get_char_input(MY_STRING user_guesses);
char evil_hangman(int len,int no_of_guesses,Boolean reveal);

int main(int argc, const char * argv[]) {
    char keep_playing = 'y';
    int len;
    int no_of_guesses;
    Boolean reveal = FALSE;
    
    while (tolower(keep_playing) == 'y') {
        len = get_word_length();
        no_of_guesses = get_no_of_guesses();
        reveal = display_answer_or_not();
        keep_playing = evil_hangman(len, no_of_guesses, reveal);
    }
    fclose(stdin);

    return 0;
}


int get_word_length(void) {
    int len = 0;
    Vector_String_Ptr word_pool;
    while (len < 2|| len > 29) {
        printf("Enter a number for the word length (2-29): ");
        scanf("%d",&len);
    }
    
    word_pool = vector_string_init_default();
    vector_string_load_one_word_of_size(len, word_pool);

    while (vector_string_empty(word_pool)) {
        printf("Can not find a word at this length.\n");
        printf("Try another number (2-29) for the word length: ");
        scanf("%d",&len);
        if (len < 2 || len > 29) {
            continue;
        }
        vector_string_load_one_word_of_size(len, word_pool);
    }
    vector_string_destroy(&word_pool);
    return len;
}

int get_no_of_guesses(void){
    int no_of_guesses = 0;
    while (no_of_guesses < 1) {
        printf("Number of guesses you need: ");
        scanf("%d",&no_of_guesses);
    }
    return no_of_guesses;
}

Boolean display_answer_or_not(void){
    Boolean reveal = FALSE;
    char reveal_input;
    printf("Display the answer?? Enter y(yes) or n(no): ");
    scanf(" %c",&reveal_input);
    if (tolower(reveal_input) == 'y') {
        reveal = TRUE;
    }
    return reveal;
}

char get_char_input(MY_STRING user_guesses){
    char c;
    int i;
    do{
        printf("\nPlease enter a letter from the English alphabet: ");
        scanf(" %c",&c);
    }while (!isalpha(c));
    c = tolower(c);

    for (i = 0 ; i <my_string_get_size(user_guesses); i++) {
        while ((c) == my_string_c_str(user_guesses)[i]) {
            printf("You entered '%c' before.\nThe letter(s) you have entered already: ",c);
            my_string_print(user_guesses);
            printf("Please try a different letter: ");
            scanf(" %c",&c);
            while(!isalpha(c)){
                printf("Please enter a letter from the English alphabet: ");
                scanf(" %c",&c);
                
            }
            c = tolower(c);
            i = 0;
        }
    }
    my_string_push_back(user_guesses, c);
    return c;
}

char evil_hangman(int len,int no_of_guesses,Boolean reveal){
    
    BinarySearchTree_Ptr hTree = NULL;
    BinaryNode_Ptr biggest_node = NULL;
    char keep_playing;
    char c;
    int i;
    MY_STRING current_word_family = my_string_init_default();
    MY_STRING user_guesses = my_string_init_default();
    
    Vector_String_Ptr dictionary = load_dictionary_of_size(len);
    
    for (i = 0; i < len; i++) {
        my_string_push_back(current_word_family, '-');
    }
    
    while (no_of_guesses--) {
        
        c = get_char_input(user_guesses);
        
        hTree = binary_search_tree_load_bst_of_words(dictionary, c, current_word_family);
        
        if (binary_search_tree_get_height(hTree)>0){
            //find biggest node if height > 0
            biggest_node = binary_search_tree_find_max(hTree);
        }
        else biggest_node = binary_search_tree_get_root(hTree);
        printf("Word: %s\n",my_string_c_str(binary_search_tree_get_node_key(biggest_node)));
        
        my_string_destroy(&current_word_family);
        current_word_family = my_string_init_c_string(my_string_c_str(binary_search_tree_get_node_key(biggest_node)));
        
        my_string_print_matched_char(current_word_family, c);
        
        vector_string_destroy(&dictionary);
        dictionary = vector_string_init_default();
        binary_search_tree_swap(hTree, (binary_search_tree_get_node_key(biggest_node)), &dictionary);
        
        if (reveal) {
            printf("I have %d word(s) left\n",vector_string_get_size(dictionary));
            printf("It maybe %s\n",my_string_c_str(*vector_string_at(dictionary, 0)));
        }
        
        printf("You entered: ");
        my_string_print(user_guesses);//print out all of user guesses
        
        //all char are correctly guessed = win
        if (!my_string_compare(*vector_string_at(dictionary, 0), current_word_family)) {
            printf("Well done! You won!!!!!\n");
            no_of_guesses = 0;
        }
        
        //keep going if still have attempts left
        if (no_of_guesses) {
            printf("You have %d attempts left\n",no_of_guesses);
        }
        
        //used up all guesses and word is still incomplete = lost
        if (!no_of_guesses && my_string_compare(*vector_string_at(dictionary, 0), current_word_family)) {
            printf("You lost!\n");
            no_of_guesses = 0;
        }
        
        binary_search_tree_destroy(&hTree);
    }
    
    if (!reveal) {
        printf("It maybe %s\n",my_string_c_str(*vector_string_at(dictionary, 0)));
    }
    
    vector_string_destroy(&dictionary);
    my_string_destroy(&current_word_family);
    my_string_destroy(&user_guesses);
    printf("\nDo you want to continue? Enter y(yes) or n(no)");
    scanf(" %c",&keep_playing);
    printf("\n");

    return keep_playing;
}
